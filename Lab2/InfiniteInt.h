//
// Created by nick434434 on 23.02.17.
//

#ifndef LAB1_INFINITEINT_H
#define LAB1_INFINITEINT_H



#include <string>
#include <vector>


const uint64_t MaxInt = 4294967296;

const uint64_t TMP_SHIFT = (MaxInt*MaxInt - MaxInt);

using std::vector;
using std::string;

class InfiniteInt {
    vector<unsigned int> _bits;
    enum Sign { PLUS, MINUS }_sign;
    unsigned long B = 32;

public:

    InfiniteInt();

    InfiniteInt(int64_t num);

    InfiniteInt(unsigned long num, unsigned int sign);

    InfiniteInt(vector<unsigned int> bits, unsigned int sign);

    InfiniteInt(vector<int64_t> bits, unsigned int sign);

    InfiniteInt(string num, unsigned int base);


    bool operator==(InfiniteInt num) const;

    bool operator<(InfiniteInt num) const;

    bool operator<=(InfiniteInt num) const;

    bool operator>(InfiniteInt num) const;

    bool operator>=(InfiniteInt num) const;


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


    void Normalize();


    string BigIntToDecimalString();

    string BigIntToString(unsigned int _base);

    vector<unsigned int> getBits();

    std::pair<int64_t, int64_t> correctDivMod(uint64_t a, uint64_t b, bool f);

    static std::pair<InfiniteInt, InfiniteInt> QuoRem(InfiniteInt divident, InfiniteInt divider);

};


#endif //LAB1_INFINITEINT_H