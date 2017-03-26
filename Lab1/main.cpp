//
// Created by nick434434 on 12.02.17.
//

#include "tests.h"
#include "make_graphs.h"

int main() {

    makeGraphs("experiments.csv");

    cout << makeTests() << endl;

    return 0;

}