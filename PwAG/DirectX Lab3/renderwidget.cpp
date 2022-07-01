#include "common.h"
#include "renderwidget.h"
#include "vertexttypes.h"

typedef Vertex_PosUV VertexType; // zmiana
typedef WORD IndexType;
const float g_ClearColor[] = {100.f/255.f, 149.f/255.f, 237.f/255.f, 1.f};

#pragma region ctors, dtor

RenderWidget::RenderWidget(float width, float height, HWND winId) :
	m_pDevice(0), m_pDebugger(0), m_pContext(0), m_pSwapChain(0), m_pRenderTargetView(0),
	m_pConstantBuffer_scene(0), m_pConstantBuffer_object(0),
	m_pTexture(0), m_pTextureSRV(0), m_pSamplerState(0),
	m_pRastState(0), m_pVertexShader(0), m_pPixelShader(0), m_pInputLayout(0), m_pVertexBuffer(0), m_pIndexBuffer(0),
	m_NumOfIndices(0), m_NumOfVertices(0), m_ObjPosX(0.f), m_ObjPosY(0.f), m_ObjPosZ(0.f),
	m_CameraDataDirty(true), m_ObjPosDataDirty(true),
	m_MouseWheelMult(0.01f), m_MouseMoveMult(50.f),
	m_CameraPosition(0.f, 0.f, -5.f), m_CameraTarget(0.f, 0.f, 0.f), m_CameraUp(0.f, 1.f, 0.f)
{

	dxInitialize(width, height, winId, true);

	m_PerfCounter.start();
}

RenderWidget::~RenderWidget()
{
	//dx clean-up:
	//1. pipeline may keep references to some objects that have been bound to it - make sure they are released
	m_pContext->ClearState();
	
	//2. release the objects used by the application
	dxReleaseCOMRefs();
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pContext);
	SAFE_RELEASE(m_pDevice);

	if(m_pDebugger)
	{
		m_pDebugger->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);		//D3D11_RLDO_DETAIL//D3D11_RLDO_SUMMARY
		SAFE_RELEASE(m_pDebugger);
	}
}

#pragma endregion

#pragma region dx

void RenderWidget::dxInitialize(float width, float height, HWND winId, bool debug)
{
	HRESULT hr; 
	DXGI_SWAP_CHAIN_DESC swapChainDesc;

	swapChainDesc = DXGI_SWAP_CHAIN_DESC();		//reset the struct

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = true;
	swapChainDesc.OutputWindow = winId;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	UINT flags = debug ? D3D11_CREATE_DEVICE_DEBUG : 0;	

	//only D3D 9.1 features are used in this lab -> no need to target "better" video cards BUT PIX does not like 9.* => 10.0
	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_10_0 };

	//http://msdn.microsoft.com/en-us/library/windows/desktop/ff476083%28v=vs.85%29.aspx
	//pAdapter: pass NULL to use the default adapter, which is the first adapter enumerated by IDXGIFactory1::EnumAdapters.
	//pFeatureLevels: A pointer to an array of D3D_FEATURE_LEVELs, which determine the order of feature levels to attempt to create. If NULL => 11.0-10.1-10.0-9.3-9.2-9.1
	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags, featureLevels, 1, D3D11_SDK_VERSION, &swapChainDesc, &m_pSwapChain, &m_pDevice, nullptr, &m_pContext);
	assert(!FAILED(hr));


	if(debug)
	{
		//ID3D11Debug interface is used for various debugging ops and is retrieved using the COM query interface techniques.
		//It also causes complete error/warning msgs to be output at runtime and enables memory leak detection as well.
		//D3D11_CREATE_DEVICE_DEBUG device creation flag must be set to enable access to the debug interface.
		hr = m_pDevice->QueryInterface(__uuidof(ID3D11Debug), (void **)&m_pDebugger);
		assert(!FAILED(hr));
	}

	dxReset(width, height);
}

void RenderWidget::dxCreateResourcesAndStateObjectsAndShaders(float width, float height)
{
	//setup view and projection matrices
	dxSetupViewAndProjection(width, height);

	//create vbs/ibs	
	dxCreateVertexBuffers();
	dxCreateIndexBuffers();
	dxCreateTextures();

	//create resource views
	dxCreateRenderTargetViews();
	dxCreateShaderResourceViews();

	//create shaders, input layouts and state objects
	ID3DBlob *vsBlob = 0, *psBlob = 0;
	dxCreateShaderObjects(vsBlob, psBlob);
	dxCreateInputLayouts(vsBlob);				//note: uses vsBlob to verify if input layout is consistent with vertex shader code
	dxCreateConstantBuffers(vsBlob, psBlob);	//note: uses vsBlob/psBlob to determine created constant buffers slots
	dxCreateSamplerStates();
	dxCreateRasterizerStates();
	SAFE_RELEASE(vsBlob);
	SAFE_RELEASE(psBlob);

	//store COM objects for which the app holds references (convenience)
	m_vToBeReleased.push_back(m_pVertexBuffer);
	m_vToBeReleased.push_back(m_pIndexBuffer);
	m_vToBeReleased.push_back(m_pTexture);
	m_vToBeReleased.push_back(m_pRenderTargetView);
	m_vToBeReleased.push_back(m_pTextureSRV);
	m_vToBeReleased.push_back(m_pConstantBuffer_scene);
	m_vToBeReleased.push_back(m_pConstantBuffer_object);	
	m_vToBeReleased.push_back(m_pVertexShader);
	m_vToBeReleased.push_back(m_pPixelShader);
	m_vToBeReleased.push_back(m_pInputLayout);
	m_vToBeReleased.push_back(m_pSamplerState);
	m_vToBeReleased.push_back(m_pRastState);
}

void RenderWidget::dxRender()
{
	updateFPS();

	if(m_CameraDataDirty)
	{
		m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_CameraPosition, m_CameraTarget, m_CameraUp);
		m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
	}
	
	dxConfigureInputAssemblerStage();
	dxConfigureVertexShaderStage(m_CameraDataDirty, m_ObjPosDataDirty);
	dxConfigureRasterizerStage();
	dxConfigurePixelShaderStage();
	dxConfigureOutputMergerStage();
	
	//clear the RT	
	m_pContext->ClearRenderTargetView(m_pRenderTargetView, g_ClearColor);

	if(m_NumOfVertices)
	{
		//draw the geometry
		if(m_NumOfIndices)
			m_pContext->DrawIndexed(m_NumOfIndices, 0, 0);
		else		
			m_pContext->Draw(m_NumOfVertices, 0);
	}

	//all the rendering in the current frame has been completed => ..
	//.. => RT contents can be presented in the client area of the render window
	m_pSwapChain->Present(0, 0);

	m_CameraDataDirty = false;
	m_ObjPosDataDirty = false;
}

void RenderWidget::dxReset(float width, float height)
{
	dxReleaseCOMRefs();
	
	//http://msdn.microsoft.com/en-us/library/windows/desktop/bb174577%28v=vs.85%29.aspx
	//set this value to DXGI_FORMAT_UNKNOWN to preserve the existing format of the back buffer
	//this "preserve trick" works the same for BufferCount, Width and Height is we set them to zeros
	//howevere, PIX does not tolerate the "preserve trick" so we explicitly set the parameters
	m_pSwapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
	
	dxSetupViewPorts(width, height);
	dxCreateResourcesAndStateObjectsAndShaders(width, height);
}

void RenderWidget::dxReleaseCOMRefs()
{
	//release all the COM objects for which the app held references
	for(std::vector<IUnknown *>::iterator it = m_vToBeReleased.begin(); it != m_vToBeReleased.end(); it++)
		SAFE_RELEASE(*it);

	m_vToBeReleased.clear();
}

void RenderWidget::dxSetupViewPorts(float width, float height)
{
	//configure the viewport
	m_ViewPort = D3D11_VIEWPORT();		//reset the struct
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_ViewPort.Width = width;
	m_ViewPort.Height = height;
}

void RenderWidget::dxCreateRenderTargetViews()
{
	HRESULT hr;

	//http://msdn.microsoft.com/en-us/library/windows/desktop/bb174570%28v=vs.85%29.aspx
	//if the swap chain's swap effect is DXGI_SWAP_EFFECT_DISCARD, this method can only access the first buffer; for this situation, set the index to zero.
	ID3D11Texture2D *pSwapChainBuffer = 0;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&pSwapChainBuffer);			//temporarily grab the swapchain buffer ptr to create an RTV
	assert(!FAILED(hr));

	hr = m_pDevice->CreateRenderTargetView(pSwapChainBuffer, nullptr, &m_pRenderTargetView);			//RTV created -> swapchain buffer ptr/address no longer needed by the app -> release
	assert(!FAILED(hr));
	SAFE_RELEASE(pSwapChainBuffer);		
}



void RenderWidget::dxCreateShaderObjects(ID3DBlob *&vsBlob, ID3DBlob *&psBlob)
{
	HRESULT hr;

	//http://msdn.microsoft.com/en-us/library/windows/desktop/jj215820%28v=vs.85%29.aspx
	//about specifying shader targets for the compiler

	//compile vertex shader
	vsBlob = nullptr;
	ShaderCompiler::Compile("../pwag03/posuv.fx", "VSMain", "vs_4_0_level_9_1", &vsBlob);			//simple VS_2.0-like shader

	//create vertex shader object
	hr = m_pDevice->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &m_pVertexShader);
	assert(!FAILED(hr));

	//compile pixel shader
	psBlob = nullptr;
	ShaderCompiler::Compile("../pwag03/posuv.fx", "PSMain", "ps_4_0_level_9_1", &psBlob);			//simple PS_2.0-like shader	

	//create pixel shader object
	hr = m_pDevice->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &m_pPixelShader);
	assert(!FAILED(hr));	
}

void RenderWidget::dxCreateInputLayouts(ID3DBlob *vsBlob)
{
	HRESULT hr;

	//define input layout for the vertex buffer
	//http://msdn.microsoft.com/en-us/library/windows/desktop/ff476180%28v=vs.85%29.aspx
	//AlignedByteOffset : use D3D10_APPEND_ALIGNED_ELEMENT for convenience to define the current element directly after the previous one, including any packing if necessary.
	std::vector<D3D11_INPUT_ELEMENT_DESC> vertexBufferElements;
	D3D11_INPUT_ELEMENT_DESC posElement = {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0};	
	D3D11_INPUT_ELEMENT_DESC texElement = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 }; // zmiana !
	vertexBufferElements.push_back(posElement);
	vertexBufferElements.push_back(texElement);

	//create the vertex buffer layout
	hr = m_pDevice->CreateInputLayout(&vertexBufferElements[0], vertexBufferElements.size(), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &m_pInputLayout);
	assert(!FAILED(hr));
}

void RenderWidget::dxCreateVertexBuffers()
{
	HRESULT hr;
	D3D11_BUFFER_DESC buffDesc;				//struct used to describe/config the vertex and index buffers	
	D3D11_SUBRESOURCE_DATA buffInitData;	//struct used to initialize the vertex and index buffers	

	//init the vertices
	std::vector<VertexType> vertices;	
	//world space rectangle
	vertices.push_back(VertexType(+0.5f, +0.5f, +0.5f, +1.0f, 0.0f)); // zmiana !
	vertices.push_back(VertexType(-0.5f, +0.5f, +0.5f, 0.0f, 0.0f));
	vertices.push_back(VertexType(-0.5f, -0.5f, +0.5f, 0.0f, +1.0f));
	vertices.push_back(VertexType(+0.5f, -0.5f, +0.5f, +1.0f, +1.0f));

	m_NumOfVertices = vertices.size();

	if(m_NumOfVertices)
	{
		//define the vertex buffer config
		buffDesc = D3D11_BUFFER_DESC();			//reset the struct
		buffDesc.ByteWidth = vertices.size() * sizeof(VertexType);
		buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		buffDesc.Usage = D3D11_USAGE_DEFAULT;
		buffDesc.CPUAccessFlags = 0;

		//set the init vertex data pointer
		buffInitData = D3D11_SUBRESOURCE_DATA();		//reset the struct	
		buffInitData.pSysMem = &vertices[0];

		//create the vertex buffer
		hr = m_pDevice->CreateBuffer(&buffDesc, &buffInitData, &m_pVertexBuffer);
		assert(!FAILED(hr));
	}
}

void RenderWidget::dxCreateIndexBuffers()
{
	HRESULT hr;
	D3D11_BUFFER_DESC buffDesc;				//struct used to describe/config the vertex and index buffers	
	D3D11_SUBRESOURCE_DATA buffInitData;	//struct used to initialize the vertex and index buffers	

	//init the indices
	std::vector<IndexType> indices;
	//any order, just keep it consistent with: rastDesc.FrontCounterClockwise & rastDesc.CullMode
	indices.push_back(1); indices.push_back(2); indices.push_back(3);
	indices.push_back(3); indices.push_back(0); indices.push_back(1);

	m_NumOfIndices = indices.size();

	if(m_NumOfIndices)
	{
		//define the index buffer config
		buffDesc = D3D11_BUFFER_DESC();			//reset the struct
		buffDesc.ByteWidth = indices.size() * sizeof(IndexType);
		buffDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		buffDesc.Usage = D3D11_USAGE_DEFAULT;
		buffDesc.CPUAccessFlags = 0;

		//set the init index data pointer
		buffInitData = D3D11_SUBRESOURCE_DATA();		//reset the struct	
		buffInitData.pSysMem = &indices[0];

		//create the index buffer
		hr = m_pDevice->CreateBuffer(&buffDesc, &buffInitData, &m_pIndexBuffer);
		assert(!FAILED(hr));
	}
}

void RenderWidget::dxCreateRasterizerStates()
{
	HRESULT hr;
	D3D11_RASTERIZER_DESC rastDesc;			//struct used to initialize the rasterizer state

	//define the rasterizer state object config
	rastDesc = D3D11_RASTERIZER_DESC();		//reset struct
	
	rastDesc.AntialiasedLineEnable = false;
	rastDesc.CullMode = D3D11_CULL_NONE;		//use D3D11_CULL_BACK/FRONT to actually do any "backface" culling
	rastDesc.DepthBias = 0;
	rastDesc.DepthBiasClamp = 0.0f;
	rastDesc.DepthClipEnable = true;
	rastDesc.FillMode = D3D11_FILL_SOLID;
	rastDesc.FrontCounterClockwise = true;
	rastDesc.MultisampleEnable = false;
	rastDesc.ScissorEnable = false;
	rastDesc.SlopeScaledDepthBias = 0.0f;

	//create the rasterizer state object
	hr = m_pDevice->CreateRasterizerState(&rastDesc, &m_pRastState);
	assert(!FAILED(hr));
}

void RenderWidget::dxCreateConstantBuffers(ID3DBlob *vsBlob, ID3DBlob *psBlob)
{
	HRESULT hr;
	D3D11_BUFFER_DESC buffDesc;				//struct used to describe/config the const buffers

	buffDesc = D3D11_BUFFER_DESC();			//reset the struct
	buffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffDesc.ByteWidth = sizeof(DirectX::SimpleMath::Matrix);
	buffDesc.Usage = D3D11_USAGE_DYNAMIC;
	buffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	buffDesc.MiscFlags = 0;

	hr = m_pDevice->CreateBuffer(&buffDesc, nullptr, &m_pConstantBuffer_scene);
	assert(!FAILED(hr));

	hr = m_pDevice->CreateBuffer(&buffDesc, nullptr, &m_pConstantBuffer_object);
	assert(!FAILED(hr));

	////////
	//http://msdn.microsoft.com/en-us/library/windows/desktop/ff476625%28v=vs.85%29.aspx
	ID3D11ShaderReflection *pReflector = nullptr; 
	hr = D3DReflect( vsBlob->GetBufferPointer(),  vsBlob->GetBufferSize(), IID_ID3D11ShaderReflection,  (void **)&pReflector); 
	assert(!FAILED(hr));

	D3D11_SHADER_INPUT_BIND_DESC desc;
	pReflector->GetResourceBindingDescByName("cb_scene", &desc);
	unsigned int sceneConstBufferSlot = desc.BindPoint;
	pReflector->GetResourceBindingDescByName("cb_object", &desc);
	unsigned int objectConstBufferSlot = desc.BindPoint;

	SAFE_RELEASE(pReflector);	
}

void RenderWidget::dxSetupViewAndProjection(float width, float height)
{
	//setup the view matrix
	m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_CameraPosition, m_CameraTarget, m_CameraUp);

	//setup the projection matrix
	float fieldOfView = (float)DirectX::XM_PI / 4.0f;
	float screenAspect = (float)width / (float)height;
	float zNear = 1.f;				//cannot be zero! about 1.0 is the common standard
	float zFar = 100.f;

	m_ProjectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, zNear, zFar);

	//setup the concat. view-projection matrix
	m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
}

void RenderWidget::dxCreateTextures()
{
	//HRESULT hr;

	//create/load textures (using DXTK helper)
	
	//hr = DirectX::CreateWICTextureFromFile(m_pDevice, L"../data/textures/gg_logo_sama_kostka.png", ?, nullptr);
	//assert(!FAILED(hr));
	HRESULT hr;
	hr = DirectX::CreateWICTextureFromFile(m_pDevice, L"../data/textures/gg_logo_sama_kostka.png", (ID3D11Resource**)&m_pTexture, nullptr); // zmiana
	assert(!FAILED(hr)); // zmiana
}

void RenderWidget::dxCreateShaderResourceViews()
{
	if(!m_pTexture) return;

	HRESULT hr;
	D3D11_SHADER_RESOURCE_VIEW_DESC shadResViewDesc;

	shadResViewDesc = D3D11_SHADER_RESOURCE_VIEW_DESC();						//reset the struct
	//shadResViewDesc.ViewDimension = ?				
	shadResViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D; // zmiana

	shadResViewDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;						//must be compatible with the actual pResource/m_pTexture format! (how to ensure this? set DXGI_FORMAT_UNKNOWN?)
	//shadResViewDesc.Texture2D.MostDetailedMip = ?;								//0 = full-size mip as the top-mip
	//shadResViewDesc.Texture2D.MipLevels = ?;									//Set to -1 to indicate all the mipmap levels from MostDetailedMip on down to least detailed
	shadResViewDesc.Texture2D.MostDetailedMip = 0; // zmiana
	shadResViewDesc.Texture2D.MipLevels = -1; // zmiana
	hr = m_pDevice->CreateShaderResourceView(m_pTexture, &shadResViewDesc, &m_pTextureSRV);
	assert(!FAILED(hr));
}

void RenderWidget::dxCreateSamplerStates()
{
	HRESULT hr;
	D3D11_SAMPLER_DESC samplerDesc;

	//create the sampler state object (for the above texture)
	samplerDesc = D3D11_SAMPLER_DESC();		//reset the struct
	samplerDesc.MaxLOD = FLT_MAX;			//for 9.* feature levels MaxLOD must be set to FLT_MAX
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	//samplerDesc.AddressU = ?;
	//samplerDesc.AddressV = ?;
	//samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;			//must be set, even for 2D textures since API won't let it through otherwise (it defaults to zero if unset)

	//hr = m_pDevice->CreateSamplerState(&samplerDesc, &m_pSamplerState);
	//assert(!FAILED(hr));

	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP; // zmiana
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;		

	hr = m_pDevice->CreateSamplerState(&samplerDesc, &m_pSamplerState);
	assert(!FAILED(hr));
}

void RenderWidget::dxConfigureInputAssemblerStage()
{
	//config the Input Assembler stage
	UINT stride = sizeof(VertexType);
	UINT offset = 0;
	m_pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	m_pContext->IASetIndexBuffer(m_pIndexBuffer, (sizeof(IndexType) == 2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT), 0);
	m_pContext->IASetInputLayout(m_pInputLayout);
	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	
}

void RenderWidget::dxConfigureVertexShaderStage(bool sceneConstantsOutdated, bool objectConstantsOutdated)
{
	HRESULT hr;
	D3D11_MAPPED_SUBRESOURCE mappedRes;

	//config the Vertex Shader stage
	m_pContext->VSSetShader(m_pVertexShader, nullptr, 0);

	if(sceneConstantsOutdated)
	{
		mappedRes = D3D11_MAPPED_SUBRESOURCE();				//reset the struct
	
		hr = m_pContext->Map(m_pConstantBuffer_scene, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedRes);
		assert(!FAILED(hr));
		memcpy(mappedRes.pData, (void *)&m_ViewProjectionMatrix, sizeof(DirectX::SimpleMath::Matrix));	
		m_pContext->Unmap(m_pConstantBuffer_scene, 0);
	}

	if(objectConstantsOutdated)
	{
		DirectX::SimpleMath::Matrix worldMatrix = DirectX::SimpleMath::Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);// DirectX::SimpleMath::Matrix::Identity;
		worldMatrix._41 = m_ObjPosX; worldMatrix._42 = m_ObjPosY; worldMatrix._43 = m_ObjPosZ;

		mappedRes = D3D11_MAPPED_SUBRESOURCE();				//reset the struct
	
		hr = m_pContext->Map(m_pConstantBuffer_object, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedRes);
		assert(!FAILED(hr));
		memcpy(mappedRes.pData, (void *)&worldMatrix, sizeof(DirectX::SimpleMath::Matrix));	
		m_pContext->Unmap(m_pConstantBuffer_object, 0);
	}

	if(sceneConstantsOutdated && objectConstantsOutdated)
	{
		ID3D11Buffer *cbuffers[2] = { m_pConstantBuffer_scene, m_pConstantBuffer_object };
		m_pContext->VSSetConstantBuffers(0, 2, cbuffers);
	}
	else if(sceneConstantsOutdated)
		m_pContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer_scene);
	else if(objectConstantsOutdated)
		m_pContext->VSSetConstantBuffers(1, 1, &m_pConstantBuffer_object);


	//in more complex apps shader resources, samplers and const buffers would be set here
	//m_pContext->VSSetShaderResources(...)
	//m_pContext->VSSetSamplers(...)	
}

void RenderWidget::dxConfigureRasterizerStage()
{	
	//config the Rasterizer stage
	m_pContext->RSSetState(m_pRastState);
	m_pContext->RSSetViewports(1, &m_ViewPort);
}

void RenderWidget::dxConfigurePixelShaderStage()
{
	//config the Pixel Shader stage
	m_pContext->PSSetShader(m_pPixelShader, nullptr, 0);

	//set shader resource views
	//m_pContext->PSSetShaderResources(0, 1, &m_pTextureSRV);

	m_pContext->PSSetShaderResources(0, 1, &m_pTextureSRV); // zmiana

	//set sampler configs
	//m_pContext->PSSetSamplers(...);	
	m_pContext->PSSetSamplers(0, 1, &m_pSamplerState); // zmiana

	//in more complex apps shader resources, samplers and const buffers would be set here	
	//m_pContext->PSSetConstantBuffers(...)


}

void RenderWidget::dxConfigureOutputMergerStage()
{
	//config the Output Merger stage
	//http://msdn.microsoft.com/en-us/library/windows/desktop/ff476464%28v=vs.85%29.aspx
	//no depth-stencil target (view) is bound => no depth-stencil state either
	m_pContext->OMSetRenderTargets(1, &m_pRenderTargetView, 0);

	//in more complex apps depth-stencil state and blend state objects would be set here
	//m_pContext->OMSetDepthStencilState(...)
	//m_pContext->OMSetBlendState(...)
}

#pragma endregion

#pragma region aux

void RenderWidget::updateFPS()
{
	double elapsed = m_PerfCounter.stop();
	m_PerfCounter.start();

	static double msSinceLastFPSUpdate = 0.0, lastFrameDuration = 0.0;
	msSinceLastFPSUpdate += elapsed;

	if(elapsed != lastFrameDuration && elapsed != 0.0 && msSinceLastFPSUpdate >= 500.0)
	{
		lastFrameDuration = elapsed;
		msSinceLastFPSUpdate = 0.0;
	}
}

#pragma endregion

#pragma region events

//void RenderWidget::resizeEvent(QResizeEvent* evt)
//{
//	dxReset();
//}

//void RenderWidget::paintEvent(QPaintEvent* evt)
//{
//	dxRender();
//}

//void RenderWidget::mousePressEvent(QMouseEvent *evt)
//{
//	if(evt->button() == Qt::LeftButton)
//	{
//		setCursor(Qt::SizeAllCursor);
//		m_CursorPrevPos	= evt->posF();
//	}
//	else if(evt->buttons() == Qt::MidButton)
//	{
//		setCursor(Qt::ClosedHandCursor);		
//		m_CursorPrevPos	= evt->posF();
//	}
//	else
//		evt->ignore();
//}
//
//void RenderWidget::mouseReleaseEvent(QMouseEvent *evt)
//{
//	setCursor(Qt::ArrowCursor);
//	evt->ignore();
//}
//
//void RenderWidget::mouseMoveEvent(QMouseEvent *evt)
//{
//	if(evt->buttons() & Qt::LeftButton)
//	{
//		QMouseEvent *e = evt;
//
//		DirectX::SimpleMath::Vector3 lastPosWC(m_CursorPrevPos.x(), m_CursorPrevPos.y(), 0.f);
//		DirectX::SimpleMath::Vector3 posWC(e->posF().x(), e->posF().y(), 0.f);
//		//screen (viewport) coors -> screen space coors
//		lastPosWC.x /= m_ViewPort.Width;
//		lastPosWC.y /= m_ViewPort.Height;
//		posWC.x /= m_ViewPort.Width;
//		posWC.y /= m_ViewPort.Height;
//		lastPosWC *= 2.f;
//		posWC *= 2.f;
//		lastPosWC -= DirectX::SimpleMath::Vector3(1.f, 1.f, 0.f);
//		posWC -= DirectX::SimpleMath::Vector3(1.f, 1.f, 0.f);
//		lastPosWC.y *= -1.0f;
//		posWC.y *= -1.0f;
//		//screen space coors -> world coors			
//		DirectX::SimpleMath::Matrix viewProjection;
//		viewProjection = m_ViewMatrix * m_ProjectionMatrix;
//		DirectX::SimpleMath::Matrix projViewWorld;	
//		projViewWorld = viewProjection.Invert();
//		lastPosWC = DirectX::SimpleMath::Vector3::Transform(lastPosWC, projViewWorld);
//		posWC = DirectX::SimpleMath::Vector3::Transform(posWC, projViewWorld);
//
//		DirectX::SimpleMath::Vector3 deltaWC = posWC - lastPosWC;
//
//		DirectX::SimpleMath::Vector3 newPos = m_CameraPosition + m_MouseMoveMult * deltaWC;
//
//		DirectX::SimpleMath::Vector3 camPosToCamTarget = m_CameraTarget - m_CameraPosition;
//		float dist = camPosToCamTarget.Length();
//
//		DirectX::SimpleMath::Vector3 newPosToCameraTarget = m_CameraTarget - newPos;
//		DirectX::SimpleMath::Vector3 dir = newPosToCameraTarget;
//		dir.Normalize();
//
//		if(fabs(dir.Dot(m_CameraUp)) < 0.99)				//block situations when camera lokat-at is parallel to camera-up
//		{
//			m_CameraPosition = m_CameraTarget - dist * dir;
//			m_CameraDataDirty = true;			
//			update();
//		}
//
//		m_CursorPrevPos	= evt->posF();
//	}
//	else if(evt->buttons() & Qt::MidButton)
//	{
//		QMouseEvent *e = evt;
//
//		DirectX::SimpleMath::Vector3 lastPosWC(m_CursorPrevPos.x(), m_CursorPrevPos.y(), 0.f);
//		DirectX::SimpleMath::Vector3 posWC(e->posF().x(), e->posF().y(), 0.f);
//		//screen (viewport) coors -> screen space coors
//		lastPosWC.x /= m_ViewPort.Width;
//		lastPosWC.y /= m_ViewPort.Height;
//		posWC.x /= m_ViewPort.Width;
//		posWC.y /= m_ViewPort.Height;
//		lastPosWC *= 2.f;
//		posWC *= 2.f;
//		lastPosWC -= DirectX::SimpleMath::Vector3(1.f, 1.f, 0.f);
//		posWC -= DirectX::SimpleMath::Vector3(1.f, 1.f, 0.f);
//		lastPosWC.y *= -1.0f;
//		posWC.y *= -1.0f;
//		//screen space coors -> world coors			
//		DirectX::SimpleMath::Matrix viewProjection;
//		viewProjection = m_ViewMatrix * m_ProjectionMatrix;
//		DirectX::SimpleMath::Matrix projViewWorld;
//		projViewWorld = viewProjection.Invert();
//		lastPosWC = DirectX::SimpleMath::Vector3::Transform(lastPosWC, projViewWorld);
//		posWC = DirectX::SimpleMath::Vector3::Transform(posWC, projViewWorld);
//
//		DirectX::SimpleMath::Vector3 deltaWC = posWC - lastPosWC;
//
//		m_CameraPosition += m_MouseMoveMult * deltaWC;
//		m_CameraTarget += m_MouseMoveMult * deltaWC;
//
//		m_CameraDataDirty = true;
//		m_CursorPrevPos	= evt->posF();
//		update();		
//	}
//	else
//		evt->ignore();	
//}
//
//void RenderWidget::wheelEvent(QWheelEvent *evt)
//{
//	DirectX::SimpleMath::Vector3 camPosToCamTarget = m_CameraTarget - m_CameraPosition;
//	DirectX::SimpleMath::Vector3 dir = camPosToCamTarget;
//	dir.Normalize();
//
//	m_CameraPosition += dir * m_MouseWheelMult * (float)evt->delta();
//
//	m_CameraDataDirty = true;
//	update();
//}

#pragma endregion