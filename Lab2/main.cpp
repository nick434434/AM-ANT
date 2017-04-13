

#include <iostream>
#include "make_graphs.h"


using std::cout;
using std::endl;


int main() {


    cout << makeTestsExtGcd() << endl;
    cout << makeTestsGcd() << endl;
    cout << makeTestsLcm() << endl;
    cout << makeTestsBinGcd() << endl;

    makeGraphs("experiments.csv");


    return 0;
}