#include "actionexec.h"

#include <random>

ReturnCode ActionExec::runNoFAILURE()
{
	counter += 1;

	random_device rd;  //Will be used to obtain a seed for the random number engine
	mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

	uniform_int_distribution<> dis(1, 4);
	int wynik = dis(gen);

	if (counter > wynik)
	{
		counter = 0;
		LOG(DEBUG) << "---> success" ;
		return ReturnCode::SUCCESS;
	}
	else
	{
		LOG(DEBUG) << "---> running" ;
		return ReturnCode::RUNNING;
	}


}


ReturnCode ActionExec::run()
{
	counter += 1;

	random_device rd;  //Will be used to obtain a seed for the random number engine
	mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	
	uniform_int_distribution<> dis(1, 4);
	int wynik = dis(gen);


	if (counter > wynik )
	{
		counter = 0;
		LOG(DEBUG) << "---> success";
		return ReturnCode::SUCCESS;
	}
	else
	{
		uniform_int_distribution<> dis2(0, 5);
		int wynik2 = dis2(gen);

		if (wynik2 <5)
		{
			LOG(DEBUG) << "---> running";
			return ReturnCode::RUNNING;
		}
		else
		{
			counter = 0;
			LOG(DEBUG) << "---> failure";
			return ReturnCode::FAILURE;
		}
	}


}