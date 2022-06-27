using UnityEngine;

public class AddShader : MonoBehaviour
{
    private Material material;

    [SerializeField]
    private Color color;
    [Range(0.1f, 2.0f)]
    public float speed;
    [Range(1, 20)]
    public int count;
    [Range(1, 2)]
    public int type;
    [Range(0.01f, 1.0f)]
    public float sprayDensity;

    private int N;

    private float progress = 0.0f;
    private int penNr = 0;

    private float[] _beginXs;
    private float[] _beginYs;

    private float[] _dirXs;
    private float[] _dirYs;

    private float[] _as;
    private float[] _bs;

    private float waitTime = 0f;

    void Awake()
    {
        material = new Material(Shader.Find("Hidden/Shader"));

        N = count;

        // punkty rysowania od początku
        _beginXs = new float[N];
        _beginYs = new float[N];

        // kierunki rysowania
        _dirXs = new float[N];
        _dirYs = new float[N];
        
        //współczynniki prostych
        _as = new float[N];
        _bs = new float[N];

        for (int i = 0; i < N; ++i)
        {
            if (Random.Range(0.0f, 1.0f) < 0.5f)
            {
                //zaczynamy od lewej
                _beginXs[i] = 0.0f;
                _beginYs[i] = Random.Range(0.1f, 0.9f);

                _dirXs[i] = Random.Range(0.1f, 1.0f);
                _dirYs[i] = _beginYs[i] < 0.5f ? Random.Range(0.01f, 0.3f) : Random.Range(-0.3f, -0.01f);
            }
            else
            {
                //zaczynamy od prawej
                _beginXs[i] = 1.0f;
                _beginYs[i] = Random.Range(0.1f, 0.9f);

                _dirXs[i] = Random.Range(-1.0f, -0.1f);
                _dirYs[i] = _beginYs[i] < 0.5f ? Random.Range(0.01f, 0.3f) : Random.Range(-0.3f, -0.01f);
            }

            _as[i] = _dirYs[i] / _dirXs[i];
            _bs[i] = _beginYs[i] - _as[i] * _beginXs[i];
        }
    }

    private void OnRenderImage(RenderTexture source, RenderTexture destination)
    {
        //ustawianie uniformów
        material.SetFloatArray("_beginXs", _beginXs);
        material.SetFloatArray("_beginYs", _beginYs);

        material.SetFloatArray("_dirXs", _dirXs);
        material.SetFloatArray("_dirYs", _dirYs);

        material.SetFloatArray("_as", _as);
        material.SetFloatArray("_bs", _bs);

        //kolor malowania
        material.SetVector("_color", color);

        // numer machnięcia pędzlem
        material.SetInt("_penNr", penNr);

        // postęp zamalowywania ekranu
        material.SetFloat("_progress", progress);

        //typ zamalowywania
        material.SetInt("_type", type);

        //gęstość spreju
        material.SetFloat("_sprayDens", sprayDensity);

        progress += Time.deltaTime * speed;

        // czekaj pomiędzy kolejnym pociągnięciem linii
        if(progress > penNr + 1)
        {
            waitTime += Time.deltaTime;

            if(waitTime > 1f)
            {
                progress = penNr + 1;
                penNr = (int)(progress);
                waitTime = 0;
            }
        }

        if (penNr > N - 1)
        {
            penNr = N - 1;
        }

        if (progress > N + 2)
        {
            progress = 0.0f;
            penNr = 0;
        }


        Graphics.Blit(source, destination, material);
    }
}
