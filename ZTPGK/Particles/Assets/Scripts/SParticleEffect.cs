using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
public class SParticle
{
	//TODO: Parametry cząsteczek 
	// oprócz samych parametrów można ustalać ich wartości początkowe lub docelowe
	//można dodawać własne
	public Vector3 position;
	public Vector3 velocity;
	public Color color;
	public Color startColor;
	public float lifeTime;
	public float maxlifeTime;
	public Vector2 endSize;
	public Vector2 size;
	
}
public class SParticleEffect : MonoBehaviour {

	Vector3[] newVertices;
	Vector2[] newUV;
	Color[] newColors;
	Renderer my_renderer;
	Camera my_camera;
	//Lista cząsteczek jest dostępna także dla klas emitera oraz afektora
	internal List<SParticle> particles = new List<SParticle> ();
	Mesh mesh;
	void Start() {
		mesh = new Mesh();
		mesh.MarkDynamic ();
		GetComponent<MeshFilter>().mesh = mesh;
		mesh.vertices = newVertices;
		mesh.uv = newUV;
		my_renderer = GetComponent<Renderer> ();
		my_camera = Camera.current;
	}
	
	// Update is called once per frame
	void Update () {
		//TODO: Renderowanie cząteczek
		//wartości z listy cząsteczek 'particles' należy skopiować do obiektu unity mesh
		//możey definiować dowolne parametry w strukturze SParticle
		//jednak należy pamiętać o tym że w Unity nie możemy definiować własnych danych wierzchołków
		//mamy do dyspozycji domyślne tablice dwuwymiarowe mesh.uv1-4 - dla tekstur - można w nich przechowywać np. rozmiar
		//trójwymiarowe - mesh.tangents mesh.normals - niewykorzystujemy ich w shaderze bilboardu więc mogą być dowolnie wykorzystane
		//oraz mesh.color dla kolorów
		//przykładowo jest przygotowana pozycja, inne parametry należy analogicznie przekopiować
		mesh.Clear ();
		int[] newind = new int[particles.Count()];
		newVertices = new Vector3[particles.Count()];
		//...
		int i = 0;
		foreach (SParticle particle in particles) {
			newVertices[i] = particle.position;
			newind[i] = i;
			//...
			i++;
		}

		mesh.vertices = newVertices;
		mesh.SetIndices (newind, MeshTopology.Points,0);
		//...
	}
}

