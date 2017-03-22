//
// Created by nick434434 on 23.02.17.
//

#ifndef LAB1_INFINITEINT_H
#define LAB1_INFINITEINT_H

#endif //LAB1_INFINITEINT_H

#include <string>
#include <vector>


#define MaxInt 4294967296

using std::vector;
using std::string;

class InfiniteInt {
    vector<unsigned int> _bits;
    enum Sign { PLUS, MINUS }_sign;
    unsigned long B = 32;

public:

    InfiniteInt();

    InfiniteInt(long long num);

    InfiniteInt(unsigned long num, unsigned int sign);

    InfiniteInt(vector<unsigned int> bits, unsigned int sign);

    InfiniteInt(vector<long long> bits, unsigned int sign);

    InfiniteInt(string num, unsigned int base);


    const bool operator==(InfiniteInt num);

    const bool operator<(InfiniteInt num);

    const bool operator<=(InfiniteInt num);

    const bool operator>(InfiniteInt num);

    const bool operator>=(InfiniteInt num);


    InfiniteInt operator+(InfiniteInt num);

    InfiniteInt operator+=(InfiniteInt num);

    InfiniteInt operator-(InfiniteInt num);

    InfiniteInt operator-=(InfiniteInt num);

    InfiniteInt operator*(InfiniteInt num);

    InfiniteInt operator*=(InfiniteInt num);

    InfiniteInt operator/(InfiniteInt num);

    InfiniteInt operator/=(InfiniteInt num);

    InfiniteInt operator%(InfiniteInt num);

    unsigned int operator[](long long i);


    InfiniteInt operator<<(unsigned int deg);

    InfiniteInt operator>>(unsigned int deg);

    InfiniteInt operator<<=(unsigned int deg);

    InfiniteInt operator>>=(unsigned int deg);


    void LevelUp();

    void Normalize();


    string BigIntToDecimalString(unsigned int _base);

    vector<unsigned int> getBits();

    unsigned int getSign();

    InfiniteInt substractBits(InfiniteInt& a, InfiniteInt& b, unsigned long bits);

    static std::pair<InfiniteInt, InfiniteInt> QuoRem(InfiniteInt divident, InfiniteInt divider);

    static std::pair<InfiniteInt, InfiniteInt> QR(InfiniteInt divident, InfiniteInt divider);

    std::pair<InfiniteInt, InfiniteInt> NewQuoRem(const InfiniteInt& lhs, const InfiniteInt & rhs);

};


