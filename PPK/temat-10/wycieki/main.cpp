

#include "nvwa/debug_new.h"

int main ()
{
    int * pint = new int [10];
    double * pdouble = new double[10];
    
    delete [] pint;  // zwolnienie pamieci
    
    // niezwolniona pamiec dla pdouble
    
    return 0;
}
