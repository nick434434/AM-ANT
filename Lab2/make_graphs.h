//
// Created by Никита Ковалев on 30.03.2017.
//

#pragma once

#ifndef LAB2_MAKE_GRAPHS_H
#define LAB2_MAKE_GRAPHS_H


#include <fstream>
#include <iostream>
#include <sstream>
#include "getCPUTime.h"
#include "gcdLib.h"

using std::cout;
using std::endl;
using std::ofstream;
using std::string;
using std::stringstream;

ofstream out;

string gen_random(const int len) {

    string res = "";
    stringstream ss;

    for (int i = 0; i < len - 1; i++) {
        ss << rand() % 10;
    }

    int num = rand() % 10;
    res = ss.str();
    ss.str(std::string()); ss.clear();
    ss << num;
    res = (ss.str() == "0" ? "1" : ss.str()) + res;

    return res;
}

bool openFile(string fname) {

    out.open(fname);
    return out.is_open();
}

void makeGraphs(string fname) {

    double start, end;

    if (openFile(fname)) {
        out << "Length" << ';' << "GCD" << ';' << "LCM" << ';' << "BIN_GCD" << ';' << "EXT_GCD" << ';' << "BIN_EXT_GCD" << endl;

        for (int i = 1; i < 100000; i += 20) {
            out << std::fixed;

            out << i << ';';
            string num1 = gen_random(i);
            string num2 = gen_random(i/2 + 100);
            //GCD
            InfiniteInt a(num1, 10);
            InfiniteInt b(num2, 10);
/*
            start = getCPUTime();
            gcd(a, b);
            end = getCPUTime();
            out << (end - start) << ';';

            cout << "gcd done" << endl;
            //LCM
            start = getCPUTime();
            lcm(a, b);
            end = getCPUTime();
            out << (end - start) << endl;
            cout << "lcm done" << endl;
*/
            //EXT_GCD
            start = getCPUTime();
            extGcd(a, b);
            end = getCPUTime();
            out << (end - start) << endl;
            cout << "ext_gcd done" << endl;

            /*
            //BIN_GCD
            start = getCPUTime();
            binaryGcd(a, b);
            end = getCPUTime();
            out << (end - start) << ';';
            cout << "bin_gcd done" << endl;

            //BIN_EXT_GCD
            start = getCPUTime();
            extBinGcd(a, b);
            end = getCPUTime();
            out << (end - start) << endl;
            cout << "bin_ext_gcd done" << endl;
            */
        }
    }

    out.close();
    return;
}

#endif //LAB2_MAKE_GRAPHS_H
