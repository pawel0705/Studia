#include "common.h"
#include "renderwidget.h"
#include "vertexttypes.h"

typedef Vertex_PosCol VertexType;
typedef WORD IndexType;
const float g_ClearColor[] = {100.f/255.f, 149.f/255.f, 237.f/255.f, 1.f};


#pragma region ctors, dtor

RenderWidget::RenderWidget(float width, float height, HWND winId) :
	m_pDevice(0), m_pDebugger(0), m_pContext(0), m_pSwapChain(0), m_pRenderTargetView(0),
	m_pDepthStencilBuffer(), m_pDepthStencilView(0), m_pDepthStencilState(0),
	m_pConstantBuffer_scene(0), m_pConstantBuffer_object(0),
	m_pTexture(0), m_pTextureSRV(0), m_pSamplerState(0),
	m_pVertexShader(0), m_pHullShader(0), m_pDomainShader(0), m_pPixelShader(0), m_pGeometryShader(0),
	m_pRastState(0), m_pInputLayout(0), m_pVertexBuffer(0), m_pIndexBuffer(0), m_pTessellationBuffer(0),
	m_NumOfIndices(0), m_NumOfVertices(0), m_ObjPosX(0.f), m_ObjPosY(0.f), m_ObjPosZ(0.f),	
	m_MouseWheelMult(0.01f), m_MouseMoveMult(50.f),
	m_CameraPosition(0.0f, -2.f, -2.f), m_CameraTarget(0.f, 0.f, 0.f), m_CameraUp(0.f, 1.f, 0.f),
	m_CameraDataDirty(true), m_ObjPosDataDirty(true), m_ForceConstBuffersUpdate(false)
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

	// D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_10_1 };
	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 }; // zmiana !

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

	dxCreateDepthStencilTextures(width, height);

	//create resource views
	dxCreateRenderTargetViews();
	dxCreateDepthStencilViews();
	dxCreateShaderResourceViews();

	//create shaders, input layouts and state objects
	ID3DBlob *vsBlob = 0, *hsBlob = 0, *dsBlob = 0, *psBlob = 0;
	dxCreateDepthStencilStates();
	dxCreateShaderObjects(vsBlob, hsBlob, dsBlob, psBlob);
	dxCreateInputLayouts(vsBlob);				//note: uses vsBlob to verify if input layout is consistent with vertex shader code
	dxCreateConstantBuffers(vsBlob, psBlob);	//note: uses vsBlob/psBlob to determine created constant buffers slots
	dxCreateSamplerStates();
	dxCreateRasterizerStates();
	SAFE_RELEASE(vsBlob);
	SAFE_RELEASE(hsBlob);
	SAFE_RELEASE(dsBlob);
	SAFE_RELEASE(psBlob);

	//store COM objects for which the app holds references (convenience)
	m_vToBeReleased.push_back(m_pVertexBuffer);
	m_vToBeReleased.push_back(m_pIndexBuffer);
	m_vToBeReleased.push_back(m_pTexture);
	m_vToBeReleased.push_back(m_pRenderTargetView);
	m_vToBeReleased.push_back(m_pDepthStencilBuffer);
	m_vToBeReleased.push_back(m_pDepthStencilView);
	m_vToBeReleased.push_back(m_pDepthStencilState);
	m_vToBeReleased.push_back(m_pTextureSRV);
	m_vToBeReleased.push_back(m_pConstantBuffer_scene);
	m_vToBeReleased.push_back(m_pConstantBuffer_object);
	m_vToBeReleased.push_back(m_pTessellationBuffer);
	m_vToBeReleased.push_back(m_pVertexShader);
	m_vToBeReleased.push_back(m_pDomainShader);
	m_vToBeReleased.push_back(m_pHullShader);
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
	dxConfigureVertexShaderStage();
	dxConfigureHullShaderStage();
	dxConfigureDomainShaderStage(m_CameraDataDirty, m_ObjPosDataDirty, m_ForceConstBuffersUpdate);
	dxConfigureRasterizerStage();
	dxConfigurePixelShaderStage();
	dxConfigureOutputMergerStage();
	
	
	//clear the RT	
	m_pContext->ClearRenderTargetView(m_pRenderTargetView, g_ClearColor);
	m_pContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

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
	m_ForceConstBuffersUpdate = false;
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
	m_ForceConstBuffersUpdate = true;
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
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;

	//http://msdn.microsoft.com/en-us/library/windows/desktop/bb174570%28v=vs.85%29.aspx
	//if the swap chain's swap effect is DXGI_SWAP_EFFECT_DISCARD, this method can only access the first buffer; for this situation, set the index to zero.
	ID3D11Texture2D *pSwapChainBuffer = 0;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&pSwapChainBuffer);			//temporarily grab the swapchain buffer ptr to create an RTV
	assert(!FAILED(hr));

	//configure the RTV
	renderTargetViewDesc = D3D11_RENDER_TARGET_VIEW_DESC();			//reset the struct
	renderTargetViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;				//specify a single mip-level to be exposed for the pipeline with the RTV

	//create the RTV
	hr = m_pDevice->CreateRenderTargetView(pSwapChainBuffer, nullptr, &m_pRenderTargetView);			//RTV created -> swapchain buffer ptr/address no longer needed by the app -> release
	assert(!FAILED(hr));
	SAFE_RELEASE(pSwapChainBuffer);		
}

void RenderWidget::dxCreateDepthStencilTextures(float width, float height)
{
	HRESULT hr;
	D3D11_TEXTURE2D_DESC tex2Desc;

	//depth stencil buffer/texture
	tex2Desc = D3D11_TEXTURE2D_DESC();			//reset the struct
	tex2Desc.Width = width;
	tex2Desc.Height = height;
	tex2Desc.MipLevels = 1;
	tex2Desc.ArraySize = 1;
	tex2Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tex2Desc.SampleDesc.Count = 1;
	tex2Desc.SampleDesc.Quality = 0;
	tex2Desc.Usage = D3D11_USAGE_DEFAULT;
	tex2Desc.CPUAccessFlags = 0;
	tex2Desc.MiscFlags = 0;
	tex2Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	//create the resource
	hr = m_pDevice->CreateTexture2D(&tex2Desc, nullptr, &m_pDepthStencilBuffer);
	assert(!FAILED(hr));
}

void RenderWidget::dxCreateDepthStencilViews()
{
	HRESULT hr;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;

	//configure DSV
	depthStencilViewDesc = D3D11_DEPTH_STENCIL_VIEW_DESC();			//reset the struct
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;				//specify a single mip-level to be exposed for the pipeline with the DSV
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	//create DSV
	hr = m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, &depthStencilViewDesc, &m_pDepthStencilView);
	assert(!FAILED(hr));
}

void RenderWidget::dxCreateDepthStencilStates()
{
	HRESULT hr;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;

	//specify depth-stencil settings of the OM
	depthStencilDesc = D3D11_DEPTH_STENCIL_DESC();			//reset the struct
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;			//D3D11_DEPTH_WRITE_MASK_ZERO is the only alternative; depth buffer writing enable/disable
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = false; //depth;

	//create the depth stencil state object
	hr = m_pDevice->CreateDepthStencilState(&depthStencilDesc, &m_pDepthStencilState);
	assert(!FAILED(hr));
}

void RenderWidget::dxCreateShaderObjects(ID3DBlob *&vsBlob, ID3DBlob *&hsBlob, ID3DBlob *&dsBlob, ID3DBlob *&psBlob)
{
	HRESULT hr;

	//http://msdn.microsoft.com/en-us/library/windows/desktop/jj215820%28v=vs.85%29.aspx
	//about specifying shader targets for the compiler

	//compile vertex shader
	vsBlob = nullptr;
	ShaderCompiler::Compile("../pwag05/shaders.fx", "VSMain", "vs_4_0_level_9_1", &vsBlob);			//simple VS_2.0-like shader

	//create vertex shader object
	hr = m_pDevice->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &m_pVertexShader);
	assert(!FAILED(hr));

	
	hsBlob = nullptr;

	// odkomentowane ! i dodane hs_5_0 zmiana
	ShaderCompiler::Compile("../pwag05/shaders.fx", "HSMain", "hs_5_0", &hsBlob);					//HS is first introduced as 5.0
	//create hull shader object
	hr = m_pDevice->CreateHullShader(hsBlob->GetBufferPointer(), hsBlob->GetBufferSize(), nullptr, &m_pHullShader);
	assert(!FAILED(hr));

	
	dsBlob = nullptr;

	// dodane ds_5_0 ! zmiana
	ShaderCompiler::Compile("../pwag05/shaders.fx", "DSMain", "ds_5_0", &dsBlob);					//DS is first introduced as 5.0
	//create domain shader object
	hr = m_pDevice->CreateDomainShader(dsBlob->GetBufferPointer(), dsBlob->GetBufferSize(), nullptr, &m_pDomainShader);
	assert(!FAILED(hr));


	//compile pixel shader
	psBlob = nullptr;
	ShaderCompiler::Compile("../pwag05/shaders.fx", "PSMain", "ps_4_0_level_9_1", &psBlob);			//simple PS_2.0-like shader	

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
	D3D11_INPUT_ELEMENT_DESC colElement = { "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	vertexBufferElements.push_back(posElement);
	vertexBufferElements.push_back(colElement);

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
	vertices.push_back(VertexType(+1.f, -1.f, 0.f, 1.f, 0.f, 0.f));
	vertices.push_back(VertexType(+1.f, +1.f, 0.f, 0.f, 1.f, 0.f));
	vertices.push_back(VertexType(-1.f, +1.f, 0.f, 0.f, 0.f, 1.f));
	vertices.push_back(VertexType(-1.f, -1.f, 0.f, 1.f, 1.f, 1.f));
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
	indices.push_back(0); indices.push_back(1); indices.push_back(2);
	indices.push_back(2); indices.push_back(3); indices.push_back(0);

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

	// dodane ! zmiana
	D3D11_BUFFER_DESC tesselationBufferDesc = D3D11_BUFFER_DESC(buffDesc);		
	tesselationBufferDesc.ByteWidth = sizeof(DirectX::SimpleMath::Vector4);	
	hr = m_pDevice->CreateBuffer(&tesselationBufferDesc, nullptr, &m_pTessellationBuffer);
	assert(!FAILED(hr));
}

void RenderWidget::dxSetupViewAndProjection(float width, float height)
{
	//setup the view matrix
	m_ViewMatrix = DirectX::XMMatrixLookAtLH(m_CameraPosition, m_CameraTarget, m_CameraUp);

	//setup the projection matrix
	float fieldOfView = (float)DirectX::XM_PI / 4.0f;
	float screenAspect = width / height;
	float zNear = 1.f;				//cannot be zero! about 1.0 is the common standard
	float zFar = 100.f;

	m_ProjectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, zNear, zFar);

	//setup the concat. view-projection matrix
	m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
}

void RenderWidget::dxCreateShaderResourceViews()
{
	if(!m_pTexture) return;

	HRESULT hr;
	D3D11_SHADER_RESOURCE_VIEW_DESC shadResViewDesc;

	shadResViewDesc = D3D11_SHADER_RESOURCE_VIEW_DESC();						//reset the struct
	shadResViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;				
	shadResViewDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;						//must be compatible with the actual pResource/m_pTexture format! (how to ensure this? set DXGI_FORMAT_UNKNOWN?)
	shadResViewDesc.Texture2D.MostDetailedMip = 0;								//0 = full-size mip as the top-mip
	shadResViewDesc.Texture2D.MipLevels = -1;									//Set to -1 to indicate all the mipmap levels from MostDetailedMip on down to least detailed
	hr = m_pDevice->CreateShaderResourceView(m_pTexture, &shadResViewDesc, &m_pTextureSRV);
	assert(!FAILED(hr));
}

void RenderWidget::dxCreateSamplerStates()
{
	HRESULT hr;
	D3D11_SAMPLER_DESC samplerDesc;

	//create the sampler state object (for the above texture)
	samplerDesc = D3D11_SAMPLER_DESC();		//reset the struct
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;			//must be set, even for 2D textures since API won't let it through otherwise
	samplerDesc.MaxLOD = FLT_MAX;								//MaxLOD must be FLT_MAX at feature level 9.*.

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
	//m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST); // zmiana !
	m_pContext->IASetInputLayout(m_pInputLayout);
}

void RenderWidget::dxConfigureVertexShaderStage()
{
	//config the Vertex Shader stage
	m_pContext->VSSetShader(m_pVertexShader, nullptr, 0);

	// zakomentowane !
	/*
	bool sceneConstantsOutdated = true, objectConstantsOutdated = true, forceCBUpdate = true;
	HRESULT hr;
	D3D11_MAPPED_SUBRESOURCE mappedRes;
	if (sceneConstantsOutdated || forceCBUpdate)
	{
		mappedRes = D3D11_MAPPED_SUBRESOURCE();				//reset the struct

		hr = m_pContext->Map(m_pConstantBuffer_scene, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedRes);
		assert(!FAILED(hr));
		memcpy(mappedRes.pData, (void *)&m_ViewProjectionMatrix, sizeof(DirectX::SimpleMath::Matrix));
		m_pContext->Unmap(m_pConstantBuffer_scene, 0);
	}
	if (objectConstantsOutdated || forceCBUpdate)
	{
		DirectX::SimpleMath::Matrix worldMatrix = DirectX::SimpleMath::Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		worldMatrix._41 = m_ObjPosX; worldMatrix._42 = m_ObjPosY; worldMatrix._43 = m_ObjPosZ;

		mappedRes = D3D11_MAPPED_SUBRESOURCE();				//reset the struct

		hr = m_pContext->Map(m_pConstantBuffer_object, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedRes);
		assert(!FAILED(hr));
		memcpy(mappedRes.pData, (void *)&worldMatrix, sizeof(DirectX::SimpleMath::Matrix));
		m_pContext->Unmap(m_pConstantBuffer_object, 0);
	}
	if ((sceneConstantsOutdated && objectConstantsOutdated) || forceCBUpdate)
	{
		ID3D11Buffer *cbuffers[2] = { m_pConstantBuffer_scene, m_pConstantBuffer_object };
		m_pContext->VSSetConstantBuffers(0, 2, cbuffers);
	}
	else if (sceneConstantsOutdated)
		m_pContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer_scene);
	else if (objectConstantsOutdated)
		m_pContext->VSSetConstantBuffers(1, 1, &m_pConstantBuffer_object);
		*/
}

void RenderWidget::dxConfigureHullShaderStage()
{
	HRESULT hr;
	m_pContext->HSSetShader(m_pHullShader, nullptr, 0);




	// dodane ! zmiana
	D3D11_MAPPED_SUBRESOURCE mappedRes = D3D11_MAPPED_SUBRESOURCE();		

	float tesselation = 10.0f;

	hr = m_pContext->Map(m_pTessellationBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedRes);
	assert(!FAILED(hr));
	memcpy(mappedRes.pData, (void*)&tesselation, sizeof(tesselation));
	m_pContext->Unmap(m_pTessellationBuffer, 0);

	m_pContext->HSSetConstantBuffers(0, 1, &m_pTessellationBuffer);
}

void RenderWidget::dxConfigureDomainShaderStage(bool sceneConstantsOutdated, bool objectConstantsOutdated, bool forceCBUpdate)
{
	m_pContext->DSSetShader(m_pDomainShader, nullptr, 0);



	// dodane z dxConfigureVertexShaderStage ! zmiana

	HRESULT hr;
	D3D11_MAPPED_SUBRESOURCE mappedRes;

	if (sceneConstantsOutdated || forceCBUpdate)
	{
		mappedRes = D3D11_MAPPED_SUBRESOURCE();				//reset the struct

		hr = m_pContext->Map(m_pConstantBuffer_scene, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedRes);
		assert(!FAILED(hr));
		memcpy(mappedRes.pData, (void*)&m_ViewProjectionMatrix, sizeof(DirectX::SimpleMath::Matrix));
		m_pContext->Unmap(m_pConstantBuffer_scene, 0);
	}
	if (objectConstantsOutdated || forceCBUpdate)
	{
		DirectX::SimpleMath::Matrix worldMatrix = DirectX::SimpleMath::Matrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		worldMatrix._41 = m_ObjPosX; worldMatrix._42 = m_ObjPosY; worldMatrix._43 = m_ObjPosZ;

		mappedRes = D3D11_MAPPED_SUBRESOURCE();				//reset the struct

		hr = m_pContext->Map(m_pConstantBuffer_object, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedRes);
		assert(!FAILED(hr));
		memcpy(mappedRes.pData, (void*)&worldMatrix, sizeof(DirectX::SimpleMath::Matrix));
		m_pContext->Unmap(m_pConstantBuffer_object, 0);
	}

	if ((sceneConstantsOutdated && objectConstantsOutdated) || forceCBUpdate)
	{
		ID3D11Buffer* cbuffers[2] = { m_pConstantBuffer_scene, m_pConstantBuffer_object };
		m_pContext->DSSetConstantBuffers(0, 2, cbuffers);
	}
	else if (sceneConstantsOutdated)
		m_pContext->DSSetConstantBuffers(0, 1, &m_pConstantBuffer_scene);
	else if (objectConstantsOutdated)
		m_pContext->DSSetConstantBuffers(1, 1, &m_pConstantBuffer_object);
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

	//set sampler configs
	m_pContext->PSSetSamplers(0, 1, &m_pSamplerState);

	//set shader resource views
	m_pContext->PSSetShaderResources(0, 1, &m_pTextureSRV);

	//in more complex apps shader resources, samplers and const buffers would be set here	
	//m_pContext->PSSetConstantBuffers(...)
}

void RenderWidget::dxConfigureOutputMergerStage()
{
	//config the Output Merger stage
	//http://msdn.microsoft.com/en-us/library/windows/desktop/ff476464%28v=vs.85%29.aspx
	//no depth-stencil target (view) is bound => no depth-stencil state either
	m_pContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	m_pContext->OMSetDepthStencilState(m_pDepthStencilState, 1);

	//in more complex apps depth-stencil state and blend state objects would be set here
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