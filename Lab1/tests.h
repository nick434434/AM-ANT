//
// Created by nick434434 on 23.02.17.
//

#ifndef LAB1_TESTS_H
#define LAB1_TESTS_H


#include "InfiniteInt.h"
#include <sstream>
#include <algorithm>
#include <iostream>

using std::stringstream;


vector<string> answersPlus = {"10000000000000000000000123", "10000000000000000000001234", "10000000000000000000012345",
"10000000000000000000123456", "10000000000000000001234567", "10000000000000000012345678",
"10000000000000000123456789", "10000000000000001234567891", "10000000000000012345678912",
"10000000000000123456789123", "10000000000001234567891234", "10000000000012345678912345",
"10000000000123456789123456", "10000000001234567891234567", "10000000012345678912345678"};

vector<string> answersMultip = {"2589741", "24787521", "246765321", "2466543321", "24664323321", "246642123321",
"2466420123321", "24664200123321", "246642000123321", "2466420000123321", "24664200000123321", "246642000000123321",
"2466420000000123321", "24664200000000123321", "246642000000000123321"};


bool makeTestsPlus() {

    string v1 = "123";
    string v2 = "10000000000000000000000000";
    bool f = true;
    for (int i = 0; i < 15 & f; i++) {
        InfiniteInt a(v1, 0);
        InfiniteInt b(v2, 0);
        a += b;
        b = InfiniteInt(answersPlus[i], 0);
        f = a == b;
        v1 += (char)((i + 3)%9 + '1');
    }

    return f;
}

bool makeTestsMinus() {

    string v1 = "10000000000000000000000000";
    string v2 = "123";
    bool f = true;
    for (int i = 0; i < 15 & f; i++) {
        InfiniteInt a(answersPlus[i], 0);
        InfiniteInt b(v2, 0);
        a -= b;
        b = InfiniteInt(v1, 0);
        f = a == b;
        v2 += (char)((i + 3)%9 + '1');
    }


    return f;
}

bool makeTestsMultiplication() {

    string v1 = "123321";
    string v2 = "21";
    bool f = true;
    for (int i = 0; i < 15 & f; i++) {
        InfiniteInt a(v1, 0);
        InfiniteInt b(v2, 0);
        a *= b;
        b = InfiniteInt(answersMultip[i], 0);
        f = a == b;
        string v3 = "20" + v2.substr(1);
        v2 = v3;
    }


    return f;
}

bool makeTestsDivision() {

    string v1 = "123321";
    string v2 = "21";
    bool f = true;
    for (int i = 0; i < 15 & f; i++) {
        InfiniteInt a(answersMultip[i], 0);
        InfiniteInt b(v2, 0);
        a /= b;
        b = InfiniteInt(v1, 0);
        f = a == b;
        string v3 = "20" + v2.substr(1);
        v2 = v3;
    }


    return f;
}

bool makeTestsDivision2() {

    string v1 = "123321";
    string v2 = "21";
    bool f = true;
    for (int i = 0; i < 15 & f; i++) {
        InfiniteInt a(answersMultip[i], 0);
        InfiniteInt b(v2, 0);
        InfiniteInt c(0);
        std::tie(a, c) = InfiniteInt::QuoRem(a, b);
        b = InfiniteInt(v1, 0);
        f = a == b;
        string v3 = "20" + v2.substr(1);
        v2 = v3;
    }


    return f;
}

static const char nums[] = "0123456789";

string randNum(unsigned long length) {
    stringstream ss;
    for (unsigned long i = 0; i < length; i++) {
        ss << std::to_string(rand() % 10);
    }
    return ss.str();
}

bool makeTestsDivisionRandom() {

    string v1 = "1";
    string v2 = "1";
    bool f = true;
    for (unsigned long i = 40; i < 70 & f; i++) {

        InfiniteInt a(v1, 0);
        InfiniteInt b(v2, 0);
        std::pair<InfiniteInt, InfiniteInt> c = InfiniteInt::QuoRem(a, b);
        b = c.first*b + c.second;
        f = a == b;
        std::cout << i << " " << f << " " << v1 << " / " << v2 << std::endl;

        v1 = randNum(i);
        v2 = randNum(i - 20);
    }


    return f;
}

bool makeTests() {
    bool f1 = makeTestsPlus();
    bool f2 = makeTestsMinus();
    bool f3 = makeTestsMultiplication();
    bool f4 = makeTestsDivision();
    bool f5 = makeTestsDivisionRandom();

    return f1 && f2 && f3 && f4 && f5;
}



#endif //LAB1_TESTS_H