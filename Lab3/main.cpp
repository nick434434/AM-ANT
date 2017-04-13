#include <iostream>
#include <NTL/ZZ.h>
#include <iomanip>
#include <fstream>
#include "getCPUTime.h"

using namespace NTL;
using std::cout;
using std::endl;


void makeFile(std::ostream& output, int n) {
    double start, end;
    output << "Length" <<";" << "Prime" << ";" << "GenPrimeTime" << ";"  << "ProbTestOnPrimeTime" << ";" << "TestOnCompTime" << endl;

    for (size_t i = 10; i <= n; i += 20) {
        ZZ tmp;
        output << i << ";";

        start = getCPUTime();
        tmp = GenPrime_ZZ(i + 1);
        end = getCPUTime();
        output << tmp << ";" << std::setprecision(10) << std::fixed << end - start << ";";

        start = getCPUTime();
        ProbPrime(tmp);
        end = getCPUTime();
        output << end - start << ";";

        start = getCPUTime();
        ProbPrime(tmp + 1);
        end = getCPUTime();
        output << end - start << endl;

    }
}


int main() {

    ZZ p = GenPrime_ZZ(25);
    cout << p << endl;

    std::cin >> p;
    cout << ProbPrime(p) << endl;

    //std::ofstream fout("out10000.csv");

    //makeFile(fout, 10000);


    return 0;
}