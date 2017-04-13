//
// Created by Никита Ковалев on 30.03.2017.
//

#pragma once

#ifndef LAB2_MAKE_GRAPHS_H
#define LAB2_MAKE_GRAPHS_H


#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include "getCPUTime.h"
#include "Fraction.h"

using std::cout;
using std::endl;
using std::ofstream;
using std::string;
using std::stringstream;

ofstream out;

string gen_random(const int len) {

    stringstream ss;

    for (int i = 0; i < len / 10; i++) {
        ss << 0;
    }
    for (int i = 0; i < ceil(double(9 * len) / 10); i++) {
        ss << rand() % 10;
    }

    return ss.str();
}

bool openFile(string fname) {

    out.open(fname);
    return out.is_open();
}

void makeGraphs(string fname) {

    double start, end;

    if (openFile(fname)) {
        out << "Length" << ';' << "Fraction" << ';' << "S" << ';' << "T" << ';' << "Time" << endl;

        for (int i = 1; i < 501; i += 1) {
            out << std::fixed;

            out << i << ';';
            string num = gen_random(i);
            out << "0." << num << ';';

            start = getCPUTime();
            Fraction a(num);
            end = getCPUTime();
            num = a.get_S_and_T();
            out << num << (end - start) << endl;

        }
    }

    out.close();
    return;
}

#endif //LAB2_MAKE_GRAPHS_H
