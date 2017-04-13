//
// Created by Никита Ковалев on 01.04.2017.
//

#ifndef INDIVIDUAL2_FRACTION_H
#define INDIVIDUAL2_FRACTION_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "InfiniteInt.h"


typedef enum {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE} Digit;



class DecimalFraction {
    vector<Digit> digits;

public:

    static inline Digit makeDigit(int dig) {
        dig %= 10;
        switch (dig) {
            case 0: return ZERO;
            case 1: return ONE;
            case 2: return TWO;
            case 3: return THREE;
            case 4: return FOUR;
            case 5: return FIVE;
            case 6: return SIX;
            case 7: return SEVEN;
            case 8: return EIGHT;
            case 9: return NINE;
            default: return ZERO;
        }
    }

    DecimalFraction(vector<int> vec) {
        this->digits.resize(vec.size());
        for (size_t i = 0; i < vec.size(); i++) {
            this->digits[i] = DecimalFraction::makeDigit(vec[i]);
        }
    }

    DecimalFraction(string s) {
        int dig = 0;
        digits.resize(s.length());
        for (size_t i = 0; i < s.length(); i++) {
            dig = s[i] - '0';
            digits[i] = makeDigit(dig);
        }
    }

    DecimalFraction(std::ostream& os, std::istream& is) {
        os << "Input decimal fraction (if fraction is 0.abcde... then type abcde...): ";
        int dig = 0;
        string s;
        is >> s;
        digits.resize(s.length());
        for (size_t i = 0; i < s.length(); i++) {
            dig = s[i] - '0';
            digits[i] = makeDigit(dig);
        }
        os << std::endl;
    }

    inline int extractDigit(size_t k) {
        int res = digits[k];
        digits.erase(digits.begin() + k - 1);
        return res;
    }

    size_t size() {
        return digits.size();
    }

    Digit& operator[](size_t i) {
        return digits[i];
    }

    friend std::ostream& operator<<(std::ostream& os, const DecimalFraction& obj) {
        os << 0 << '.';
        for (size_t i = 0; i < obj.digits.size(); i++)
            os << obj.digits[i];
        return os;
    }
};

typedef DecimalFraction DecFr;


class Fraction {
    Iint s;
    Iint t;

    Iint M;

public:

    Fraction() : s(0), t(1), M(2) {}

    Fraction(const Iint a, const Iint b) : s(a), t(b), M(Iint(b)*2) {}

    Fraction(DecFr fr);

    static Iint tenInDegree(uint64_t k);

    friend std::ostream& operator<<(std::ostream& os, const Fraction& obj);

    string get_S_and_T();
};


#endif //INDIVIDUAL2_FRACTION_H
