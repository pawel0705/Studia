
#include <iostream>
#include <string>
#include <random>


#include "node.h"
#include "returncode.h"

#include "actionexec.h"

#include "log.h"
// https://stackoverflow.com/questions/5028302/small-logger-class


using namespace std;

structlog LOGCFG = {};

ActionExec exec;


ReturnCode succ_fail()
{
	random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> dis(0,1);
	int true_false = dis(gen);
	if (true_false==1)
	{
		LOG(DEBUG) << "---> success" ;
		return ReturnCode::SUCCESS;	
	}
	else 
	{
		LOG(DEBUG) << "---> failure" ;
		return ReturnCode::FAILURE;	
	}
}

ReturnCode succ_runn()
{
	random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> dis(0,1);
	int true_false = dis(gen);
	if (true_false == 1)
	{
		LOG(DEBUG) << "---> success" ;
		return ReturnCode::SUCCESS;
	}
	else
	{
		LOG(DEBUG) << "---> running" ;
		return ReturnCode::RUNNING;
	}
}


ReturnCode predEnergia()
{
	
	LOG(DEBUG) << "Czy ma energie?:";
   	
	return succ_fail();
	
}

ReturnCode predPogoda()
{
   	LOG(DEBUG) << "Czy jest ladna pogoda?:" ;
   	return succ_fail();
	
}


ReturnCode actionBieganie()
{
	LOG(DEBUG) << "Biega:";
	return exec.run();
	// return succ_runn();
}


ReturnCode actionSilownia()
{
	LOG(DEBUG) << "Na silowni:";
	return exec.run();
	// return succ_runn();
}

ReturnCode actionPlywanie()
{
	LOG(DEBUG) << "Plywa:";
	return exec.run();
	// return succ_runn();
}

ReturnCode actionTelefon()
{
	LOG(DEBUG) << "Dzwoni do przyjaciela:";
	return exec.run();
	// return succ_runn();
}

ReturnCode actionSpotkanie()
{
	LOG(DEBUG) << "Spotkanie z przyjacielem:";
	return exec.runNoFAILURE();
	// return succ_runn();
}

ReturnCode actionTV()
{
	LOG(DEBUG) << "Oglad TV:";
	return exec.runNoFAILURE();
	// return succ_runn();
}

ReturnCode actionSen()
{
	LOG(DEBUG) << "Spi:";
	return exec.runNoFAILURE();
	// return succ_runn();
}

int main(int argc, char const *argv[])
{

	LOGCFG.headers = false; 
    LOGCFG.level = DEBUG;

	//LOG(INFO) << "Main executed with " << (argc - 1) << " arguments";

//******************************************************
//Definicja BT ****************************************
//******************************************************
	Selector *selCzasWolny = new Selector();
	{
		Sequence *seq_WypAktywny = new Sequence();
		selCzasWolny->addChild(seq_WypAktywny);
		{
			Conditional *cond_Energia = new Conditional(predEnergia);
			seq_WypAktywny->addChild(cond_Energia);

			Selector *sel_WypAktywny = new Selector();
			seq_WypAktywny->addChild(sel_WypAktywny);
			{
				Sequence *seq_WypAktywnyPogoda = new Sequence();
				sel_WypAktywny->addChild(seq_WypAktywnyPogoda);
				{
					Conditional *cond_Pogoda = new Conditional(predPogoda);
					seq_WypAktywnyPogoda->addChild(cond_Pogoda);

					Action * act_Bieganie = new Action(actionBieganie);
					seq_WypAktywnyPogoda->addChild(act_Bieganie);
				}

				Sequence *seq_WypAktywnyNiePogoda = new Sequence();
				sel_WypAktywny->addChild(seq_WypAktywnyNiePogoda);
				{
					Action *act_Silownia = new Action(actionSilownia);
					seq_WypAktywnyNiePogoda->addChild(act_Silownia);

					Action * act_Plywanie = new Action(actionPlywanie);
					seq_WypAktywnyNiePogoda->addChild(act_Plywanie);
				}
			}
		}

		Sequence *seq_Przyjaciele = new Sequence();
		selCzasWolny->addChild(seq_Przyjaciele);
		{
			Action *act_Tel = new Action(actionTelefon);
			seq_Przyjaciele->addChild(act_Tel);

			Action * act_Spotkanie = new Action(actionSpotkanie);
			seq_Przyjaciele->addChild(act_Spotkanie);
		}

		Sequence *seq_Dom = new Sequence();
		selCzasWolny->addChild(seq_Dom);
		{
			Action *act_TV = new Action(actionTV);
			seq_Dom->addChild(act_TV);

			Action * act_Spanie = new Action(actionSen);
			seq_Dom->addChild(act_Spanie);
		}
	}
//******************************************************
//******************************************************

	ReturnCode result;
	result = selCzasWolny->tick();
	
	char c = 0;
	while (c!='q')
	{

		
		for (int i = 0; i < 15; ++i)
		{
			LOG(DEBUG) << "count: " << exec.getCounter();
			LOG(INFO) << "---------- new iteration --------- " << i << " -----------";
			result = selCzasWolny->tick();
			if (result != ReturnCode::RUNNING)
			{
				LOG(INFO) << "---------- End Tree --------- ";
				break;
			}
		}
		LOG(DEBUG) << "\'q\' aby zakonczyc. " ;

		c=cin.get();
	}


	return 0;
}
