//
// Created by nick434434 on 23.02.17.
//

#pragma once

#ifndef LAB1_INFINITEINT_H
#define LAB1_INFINITEINT_H



#include <string>
#include <vector>


const uint64_t MaxInt = 4294967296;

const uint64_t TMP_SHIFT = (MaxInt*MaxInt - MaxInt);


using std::vector;
using std::string;

enum Sign { PLUS, MINUS };

class InfiniteInt {
    vector<unsigned int> _bits;
    Sign _sign = PLUS;
    unsigned long B = 32;

public:

    InfiniteInt();

    InfiniteInt(int64_t num);

    InfiniteInt(double d, unsigned int base);

    InfiniteInt(unsigned long num, Sign sign);

    InfiniteInt(vector<unsigned int> bits, unsigned int sign);

    InfiniteInt(vector<int64_t> bits, unsigned int sign);

    InfiniteInt(string num, unsigned int base);

    InfiniteInt(string num) : InfiniteInt(num, 10) {}

    bool operator==(InfiniteInt num) const;

    bool operator<(InfiniteInt num) const;

    bool operator<=(InfiniteInt num) const;

    bool operator>(InfiniteInt num) const;

    bool operator>=(InfiniteInt num) const;


    bool operator<(double d) const;
    bool operator>(double d) const;
    bool operator<=(double d) const;
    bool operator>=(double d) const;


    InfiniteInt operator+(InfiniteInt num);

    InfiniteInt operator+=(InfiniteInt num);

    InfiniteInt operator-(InfiniteInt num);

    InfiniteInt operator-=(InfiniteInt num);

    InfiniteInt operator*(InfiniteInt num);

    InfiniteInt operator*=(InfiniteInt num);

    InfiniteInt operator/(InfiniteInt num);

    InfiniteInt operator/=(InfiniteInt num);

    InfiniteInt operator%(InfiniteInt num);

    unsigned int& operator[](size_t i);


    InfiniteInt operator<<(unsigned int deg);

    InfiniteInt operator>>(unsigned int deg);

    InfiniteInt operator<<=(unsigned int deg);

    InfiniteInt operator>>=(unsigned int deg);

    friend std::ostream& operator<<(std::ostream& os, const InfiniteInt& obj);


    void Normalize();


    string BigIntToDecimalString() const;

    string BigIntToString(unsigned int _base) const;

    vector<unsigned int> getBits();

    std::pair<int64_t, int64_t> correctDivMod(uint64_t a, uint64_t b, bool f);

    static std::pair<InfiniteInt, InfiniteInt> QuoRem(InfiniteInt divident, InfiniteInt divider);

    InfiniteInt sqrt();

    double quotientToDouble(InfiniteInt a, InfiniteInt b);

};


typedef InfiniteInt Iint;


#endif //LAB1_INFINITEINT_H