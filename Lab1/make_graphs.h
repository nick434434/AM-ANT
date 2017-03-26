//
// Created by nick434434 on 02.03.17.
//

#ifndef LAB1_MAKE_GRAPHS_H
#define LAB1_MAKE_GRAPHS_H


#include <fstream>
#include <ctime>
#include <iostream>
#include "getCPUTime.h"

using std::cout;
using std::endl;
using std::ofstream;

ofstream out;


string gen_random(const int len) {

    string res = "";

    for (int i = 0; i < len - 1; i++)
        res = res + std::to_string(rand() % 10);

    int num = rand() % 10;
    res = (std::to_string(num) == "0" ? "1" : std::to_string(num)) + res;

    return res;
}

bool openFile(string fname) {

    out.open(fname);
    return out.is_open();
}

void makeGraphs(string fname) {

    double start, end;



    if (openFile(fname)) {
        out << "Length" << ';' << "Input" << ';' << "Sum" << ';' << "Substract" << ';' << "Multipl" << ';' << "Divide1" << ';'
            << "Divide2" << ';' << "OutputToStr" << endl;

        for (int i = 1; i < 10000; i += 20) {
            out << std::fixed;

            out << i << ';';
            string num1 = gen_random(i);
            string num2 = gen_random(i);
            string num3 = gen_random(i/2);
            //INPUT
            start = getCPUTime();
            InfiniteInt a(num1, 10);
            end = getCPUTime();
            InfiniteInt b(num2, 10);
            out << (end - start) << ';';

            //SUM
            InfiniteInt c(0);
            start = getCPUTime();
            c = a + b;
            end = getCPUTime();
            out << (end - start) << ';';

            //SUBSTRACTION
            start = getCPUTime();
            c = a - b;
            end = getCPUTime();
            out << (end - start) << ';';

            //MULTIPLICATION
            start = getCPUTime();
            c = a * b;
            end = getCPUTime();
            out << (end - start) << ';';


            //DIVISION
            InfiniteInt d(num3, 10);
            start = getCPUTime();
            c = a / d;
            end = getCPUTime();
            out << (end - start) << ';';
            //SECOND DIVISION
            start = getCPUTime();
            c = b / d;
            end = getCPUTime();
            out << (end - start) << ';';

            //OUTPUT
            start = getCPUTime();
            a.BigIntToDecimalString(10);
            end = getCPUTime();
            out << (end - start) << endl;

        }
    }

    out.close();
    return;
}


#endif //LAB1_MAKE_GRAPHS_H