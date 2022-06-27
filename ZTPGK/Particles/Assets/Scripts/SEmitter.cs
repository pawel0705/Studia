using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
public class SEmitter : MonoBehaviour 
{

	// Use this for initialization
	void Start () 
	{
	
	}
	float NRand()
	{
		const int q = 15;
		const float c1 = (float)((1 << q) - 1);
		const float c2 = (float)(((int)(c1 / 3)) + 1);
		const float c3 = 1.0f / c1;
		/* random number in range 0 - 1 not including 1 */
		float random = Random.value;
		random = (2.0f * ((random * c2) + (random * c2) + (random * c2)) - 3.0f * (c2 - 1.0f)) * c3;
		return random;
	}
	// Update is called once per frame
	void Update () 
	{
		//TODO: Należy utworzyć nowe cząsteczki i przypisać im początkowe parametry (ewentualnie docelowe)
		//parametry powinny być ustalone na podstawie liczb losowych  - do tego można
		//wykorzystywać Random.value lub NRand() - rozkład Gaussa - większe zagęszczenie w okół zera
		//niektóre parametry warto uzależnić od zmiennych publicznych które można ustalawiać w edytorze Unity
		SParticleEffect pEffect = this.GetComponent<SParticleEffect>();
		List<SParticle> allParticles = pEffect.particles;
		for (int i = 0; i < 2; i++) 
		{
			SParticle newParticle = new SParticle()
			{
				maxlifeTime = NRand()+9.0f
				//...
			};
			allParticles.Add(newParticle);
		}
		//Tutaj cząsteczki są usuwane
		allParticles.ForEach(currP => currP.lifeTime += Time.deltaTime);
		allParticles.RemoveAll(currP => currP.lifeTime>currP.maxlifeTime);
	}
}
