//
// Created by nick434434 on 12.02.17.
//

#include "tests.h"
#include "make_graphs.h"

std::pair<long long, long long> correctDM(__int128 a, __int128 b) {
    long long q = a / b;
    long long r = a % b;
    if (q >= 0)
        return std::make_pair(q, r);
    else
        return std::make_pair(q - 1, r + b);
};

int main() {


    makeGraphs("experiments.csv");



    InfiniteInt a("2466420000123321", 10);
    InfiniteInt b("20000000001", 10);


    std::pair<InfiniteInt, InfiniteInt> c = InfiniteInt::QuoRem(a, b);

    InfiniteInt e("123321", 10);

    InfiniteInt d = c.first*b + c.second;


    cout << makeTestsDivision2() << endl;
    cout << makeTests() << endl;

    cout << makeTestsDivisionRandom() << endl;

    return 0;

}