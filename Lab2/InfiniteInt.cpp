//
// Created by nick434434 on 23.02.17.
//


#include "InfiniteInt.h"
#include <iostream>
#include <tuple>
#include <algorithm>
#include <sstream>


using std::cout;
using std::endl;
using std::pair;
using std::make_pair;
using std::stringstream;


InfiniteInt::InfiniteInt() {
    _bits.resize(1, 0);
    _sign = PLUS;
}

InfiniteInt::InfiniteInt(int64_t num) {
    num >= 0 ? _sign = PLUS : _sign = MINUS;
    _bits.resize(1, (uint32_t)abs(num));
}

InfiniteInt::InfiniteInt(double d, unsigned int base) {
    stringstream ss;
    ss << std::fixed << trunc(d);
    *this = InfiniteInt(ss.str().substr(0, ss.str().length() - 7), base);
}

InfiniteInt::InfiniteInt(unsigned long num, Sign sign) {
    _bits.resize(1, num);
    _sign = sign;
    std::reverse(this->_bits.begin(), this->_bits.end());
}

InfiniteInt::InfiniteInt(vector<unsigned int> bits, unsigned int sign) {
    _bits = bits;
    _sign = sign ? MINUS : PLUS;
    Normalize();
}

InfiniteInt::InfiniteInt(vector<int64_t> bits, unsigned int sign) {
    _bits.resize(bits.size(), 0);

    for (size_t i = 0; i < bits.size(); i++)
        _bits[i] += (unsigned int)bits[i];

    _sign = sign ? MINUS : PLUS;
    Normalize();
}

InfiniteInt::InfiniteInt(string num, unsigned int base) {

    if (num[0] == '-') {
        _sign = MINUS;
        //Get rid of the '-'
        num = num.substr(1);
    }
    else _sign = PLUS;

    _bits.resize(1, 0);

    int64_t carry, tmp, digit;

    for (long i = 0; i < num.size(); i++) {
        carry = num[i] - '0';

        for (signed long j = _bits.size() - 1; j >= 0; j--) {
            digit = _bits[j];
            tmp = digit * 10 + carry;
            _bits[j] = tmp % ((int64_t)MaxInt);
            carry = tmp / ((int64_t)MaxInt);
        }

        if (carry)
            _bits.insert(_bits.begin(), carry);
    }



    this->Normalize();
    std::reverse(this->_bits.begin(), this->_bits.end());
}

bool InfiniteInt::operator==(InfiniteInt num) const {
    return _sign == num._sign && _bits == num._bits;
}

bool InfiniteInt::operator<=(InfiniteInt num) const {
    if (_sign != num._sign)
        return _sign ? true : false;
    else {
        bool f = true;
        unsigned long k = _bits.capacity();
        unsigned long l = num._bits.capacity();

        if (k < l)
            f = true;
        else if (k > l)
            f = false;
        else
            for (unsigned long i = k; i > 0 && f; i--) {
                f = f && _bits[i - 1] <= num._bits[i - 1];
                if (_bits[i - 1] < num._bits[i - 1])
                    return true;
            }

        if (_sign == MINUS)
            f = 1 - f;

        return f;
    }
}

bool InfiniteInt::operator<(InfiniteInt num) const {
    return *this <= num && !(*this == num);
}

bool InfiniteInt::operator>=(InfiniteInt num) const {
    return *this > num || *this == num;
}

bool InfiniteInt::operator>(InfiniteInt num) const {
    return num < *this;
}

InfiniteInt InfiniteInt::operator+(InfiniteInt num) {

    if (_sign == num._sign) {
        unsigned long k = _bits.capacity();
        unsigned long l = num._bits.capacity();

        vector<unsigned int> res;
        res.resize(k > l ? k + 1 : l + 1, 0);

        unsigned long min_length = k > l ? l : k;
        int carry = 0;
        int64_t tmp = 0;

        for (int i = 0; i < min_length; i++) {
            tmp = (int64_t)_bits[i] + (int64_t)num._bits[i] + (int64_t)carry;
            carry = tmp / MaxInt;
            res[i] = tmp % MaxInt;
        }
        for (unsigned long i = min_length; i < res.capacity() - 1; i++) {
            tmp = (int64_t)(k > l ? _bits[i] : num._bits[i]) + (int64_t)carry;
            carry = tmp / MaxInt;
            res[i] = tmp % MaxInt;
        }

        if (carry)
            res[res.capacity() - 1] = carry;

        InfiniteInt result = InfiniteInt(res, _sign);
        result.Normalize();
        return result;
    }
    else {
        if (_sign) {
            InfiniteInt num1(_bits, 0);
            return num - num1;
        }
        else {
            InfiniteInt num1(num._bits, 0);
            return *this - num1;
        }
    }


}

InfiniteInt InfiniteInt::operator+=(InfiniteInt num) {
    *this = *this + num;
    return *this;
}

InfiniteInt InfiniteInt::operator-(InfiniteInt num) {
    if (_sign == num._sign) {
        unsigned long k = _bits.capacity();
        unsigned long l = num._bits.capacity();

        vector<unsigned int> res;
        vector<unsigned int> minuend;
        vector<unsigned int> substrahend;
        unsigned int sign;



        if (*this > num) {
            sign = 0;
            res.resize(k, 0);
            if (_sign) {
                minuend = num._bits;
                substrahend = _bits;
            }
            else {
                minuend = _bits;
                substrahend = num._bits;
            }
        }
        else {
            sign = 1;
            res.resize(l, 0);
            if (_sign) {
                minuend = _bits;
                substrahend = num._bits;
            }
            else {
                minuend = num._bits;
                substrahend = _bits;
            }
        }

        unsigned long min_length = k > l ? l : k;
        int carry = 0;
        int64_t tmp = 0;

        for (int i = 0; i < min_length; i++) {
            tmp = (int64_t)minuend[i] - (int64_t)substrahend[i] + (int64_t)carry;
            if (tmp >= 0)
                carry = (int64_t )tmp / (int64_t )MaxInt;
            else {
                carry = -1;
                tmp += ((int64_t)1 << 32);
            }
            res[i] = (int64_t)tmp % (int64_t)MaxInt;
        }
        for (unsigned long i = min_length; i < res.capacity(); i++) {
            tmp = (int64_t)minuend[i] + (int64_t)carry;
            if (tmp >= 0)
                carry = (int64_t)tmp / (int64_t)MaxInt;
            else {
                carry = -1;
                tmp += ((int64_t)1 << 32);
            }
            res[i] = (int64_t)tmp % (int64_t)MaxInt;
        }

        InfiniteInt result = InfiniteInt(res, sign);
        result.Normalize();
        return result;
    }
    else
    if (_sign) {
        InfiniteInt num1(num._bits, 1);
        return num1 + *this;
    }
    else {
        InfiniteInt num1(num._bits, 0);
        return num1 + *this;
    }

}

InfiniteInt InfiniteInt::operator-=(InfiniteInt num) {
    *this = *this - num;
    return *this;
}

InfiniteInt InfiniteInt::operator*(InfiniteInt num) {

    unsigned int sign = (unsigned int)(_sign != num._sign);

    unsigned long k = _bits.capacity();
    unsigned long l = num._bits.capacity();

    vector<unsigned int> res;
    res.resize(k + l, 0);

    unsigned long carry = 0;
    uint64_t tmp = 0;

    for (int i = 0; i < k + l; i++)
        res[i] = 0;

    for (int i = 0; i < k; i++) {
        carry = 0;
        for (int j = 0; j < l; j++) {
            tmp = (uint64_t)_bits[i] * (uint64_t)num._bits[j] + (uint64_t)res[i + j]
                  + (uint64_t)carry;
            carry = tmp / MaxInt;
            res[i + j] = tmp % MaxInt;
        }
        res[i + l] = carry;
    }

    InfiniteInt result(res, sign);
    result.Normalize();

    return result;
}

InfiniteInt InfiniteInt::operator*=(InfiniteInt num) {
    *this = *this * num;
    return *this;
}

InfiniteInt InfiniteInt::operator/(InfiniteInt num) {

    return QuoRem(*this, num).first;

}

InfiniteInt InfiniteInt::operator/=(InfiniteInt num) {
    *this = *this / num;
    return *this;
}

InfiniteInt InfiniteInt::operator%(InfiniteInt num) {

    return QuoRem(*this, num).second;
}

InfiniteInt InfiniteInt::operator<<(unsigned int deg) {
    if (deg == 0)
        return *this;

    unsigned int rb, lb;
    vector<unsigned int> newBits(_bits.size());

    lb = 0;
    for (int i = 0; i < _bits.size(); i++) {
        rb = _bits[i] & ((1 << (B - deg)) - 1);
        newBits[i] = (rb << deg) + lb;
        lb = _bits[i] >> (B - deg);
    }

    if (lb) {
        newBits.resize(newBits.size() + 1, 1);
        newBits[newBits.size() - 1] = lb;
    }

    InfiniteInt res(newBits, _sign);
    res.Normalize();

    return res;
}

InfiniteInt InfiniteInt::operator>>(unsigned int deg) {
    unsigned int rb, lb;
    vector<unsigned int> newBits(_bits.size());

    for (int i = 0; i < _bits.size(); i++) {
        lb = _bits[i] >> deg;
        rb = (i == _bits.size() - 1) ? 0 :
             _bits[i + 1] & ((1 << deg) - 1);
        newBits[i] = (rb << (B - deg)) + lb;
    }

    InfiniteInt res(newBits, _sign);
    res.Normalize();

    if ( (_sign == MINUS) && !((*this % 2) == 0) )
        res -= 1;

    return res;
}

InfiniteInt InfiniteInt::operator<<=(unsigned int deg) {
    return (*this = *this << deg);
}

InfiniteInt InfiniteInt::operator>>=(unsigned int deg) {
    return (*this = *this >> deg);
}

std::ostream &operator<<(std::ostream &os, const InfiniteInt &obj) {
    os << obj.BigIntToDecimalString();
    return os;
}

unsigned int& InfiniteInt::operator[](size_t i) {
    return this->_bits[i];
}



void InfiniteInt::Normalize() {
    unsigned long l = _bits.capacity();
    for (unsigned long i = l - 1; i > 0 && _bits[i] == 0; i--)
        _bits.resize(i);
    _bits.shrink_to_fit();
    if ( (_bits.size() <= 1) && _bits[0] == 0)
        _sign = PLUS;
}

string InfiniteInt::BigIntToString(unsigned int _base) const {
    if ( (_bits.size() <= 1) && _bits[0] == 0)
        return "0";

    string res = "";
    InfiniteInt base(_base, PLUS);
    InfiniteInt tmp(this->_bits, PLUS);
    stringstream ss;

    for (; tmp._bits.size() > 1 || tmp._bits[0] > 0;) {
        ss << (tmp % base).getBits()[0];
        res = ss.str() + res;
        tmp = tmp / base;
        ss.str(std::string()); ss.clear();
    }

    if (this->_sign == MINUS)
        res = '-' + res;

    return res;
}

string InfiniteInt::BigIntToDecimalString() const {
    return this->BigIntToString(10);
}

vector<unsigned int> InfiniteInt::getBits() {
    return _bits;
}



pair<int64_t, int64_t> InfiniteInt::correctDivMod(uint64_t a, uint64_t b, bool f) {
    if (!f)
        return make_pair(a / b, a % b);
    else {
        int64_t q = a / b;
        int64_t r = a % b;
        r = -(r - b);
        if (r >= MaxInt)
            r = r - MaxInt;
        return make_pair(r == 0 ? q : q + 1, r);
    }

};

pair<InfiniteInt, InfiniteInt> InfiniteInt::QuoRem(InfiniteInt d_dent, InfiniteInt d_der) {
    if (d_der == 0) {
        cout << "Division by zero!" << endl;
        return make_pair(d_dent, d_der);
    }
    else {
        int w = 0;
        InfiniteInt divident = d_dent;
        InfiniteInt divider = d_der;
        divident._sign = PLUS;
        divider._sign = PLUS;
        unsigned long lenDivider = divider._bits.size();

        if (divident >= divider) {
            while (divider._bits[divider._bits.size() - 1] < MaxInt / 2) {
                divident <<= 1;
                divider <<= 1;
                w++;
            }

            vector<int64_t> quot;
            vector<int64_t> rem;

            unsigned long k = divident._bits.size();
            unsigned long l = divider._bits.size();

            rem.resize(k > l ? k + 1 : l + 1, 0);
            quot.resize(k - l + 1 > 0 ? k - l + 1 : 1, 0);

            uint32_t carry = 0;
            uint64_t tmp = 0;

            for (int i = 0; i < k; i++)
                rem[i] = divident._bits[i];

            for (int64_t i = k - l; i >= 0; i--) {
                tmp = (((uint64_t) rem[i + l]) << 32) | (uint64_t) rem[i + l - 1];
                carry = divider._bits[l - 1];
                quot[i] = (int64_t) floor(tmp / carry);

                if (quot[i] >= MaxInt)
                    quot[i] = MaxInt - 1;
                carry = 0;

                for (int j = 0; j < l; j++) {
                    tmp = (uint64_t) TMP_SHIFT - (uint64_t) quot[i] * (uint64_t) divider._bits[j] - carry +
                          (uint64_t) rem[i + j];
                    bool f = tmp <= TMP_SHIFT;

                    std::tie(carry, rem[i + j]) = divident.correctDivMod(
                            f ? (uint64_t) TMP_SHIFT - tmp : tmp - (uint64_t) TMP_SHIFT, (uint64_t) MaxInt, f);

                }

                rem[i + l] -= carry;

                for (; rem[i + l] < 0;) {
                    carry = 0;
                    for (int j = 0; j < l; j++) {
                        tmp = (uint64_t) rem[i + j] + (uint64_t) divider._bits[j] + carry;

                        std::tie(carry, rem[i + j]) = divident.correctDivMod(tmp, (uint64_t) MaxInt, 0);

                    }
                    rem[i + l] += carry;
                    quot[i]--;
                }
            }


            InfiniteInt quo(quot, d_dent._sign ^ d_der._sign);
            InfiniteInt re(rem, d_der._sign);

            quo.Normalize();
            re.Normalize();

            re >>= w;

            if (re == d_der) {
                re = 0;
                quo += 1;
            } else if (!(d_dent == quo * d_der + re)) {
                re = d_der - re;
                re._sign = d_der._sign;
                quo += quo._sign ? InfiniteInt(1, MINUS) : InfiniteInt(1, PLUS);
            }

            return make_pair(quo, re);
        } else {
            if (divident > 0) {
                if (divider > 0)
                    return make_pair(0, divident);
                else
                    return make_pair(-1, divider * (-1) - divident);
            }
            if (divident < 0)
                if (divider > 0)
                    return make_pair(-1, divident - divider * (-1));
                else
                    return make_pair(0, divident);
        }
    }
}

InfiniteInt InfiniteInt::sqrt() {
    InfiniteInt a = *this;
    InfiniteInt x0 = a, x1 = (a + 1) >> 1;
    while (x1 < x0) {
        x0 = x1;
        x1 = (x1 + a / x1) >> 1;
    }
    return x0;
}

bool InfiniteInt::operator<(double d) const {
    Iint dI = (int64_t )ceil(d);
    return *this < dI;
}

bool InfiniteInt::operator<=(double d) const {
    Iint dI = (int64_t )ceil(d);
    return *this <= dI;
}

bool InfiniteInt::operator>(double d) const {
    Iint dI = (int64_t )floor(d);
    return *this > dI;
}

bool InfiniteInt::operator>=(double d) const {
    Iint dI = (int64_t )floor(d);
    return *this >= dI;
}

double InfiniteInt::quotientToDouble(InfiniteInt a, InfiniteInt b) {
    double d = 0;
    string divider = b.BigIntToDecimalString();
    size_t shift = divider.length();

    d = atoi(a.BigIntToDecimalString().c_str());
    for (size_t i = 0; i < shift; i++)
        d *= 10;
    d = trunc(d);

    InfiniteInt r(d, 10);


    return d;
}


