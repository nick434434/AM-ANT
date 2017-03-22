//
// Created by nick434434 on 23.02.17.
//


#include "InfiniteInt.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cmath>

using std::cout;
using std::endl;
using std::pair;
using std::make_pair;

InfiniteInt::InfiniteInt() {
    _bits.resize(1, 0);
    _sign = PLUS;
}

InfiniteInt::InfiniteInt(long long num) {
    num >= 0 ? _sign = PLUS : _sign = MINUS;
    _bits.resize(1, (unsigned int)num);
    std::reverse(this->_bits.begin(), this->_bits.end());
}

InfiniteInt::InfiniteInt(unsigned long num, unsigned int sign) {
    _bits.resize(1, num);
    _sign = sign ? MINUS : PLUS;
    std::reverse(this->_bits.begin(), this->_bits.end());
}

InfiniteInt::InfiniteInt(vector<unsigned int> bits, unsigned int sign) {
    _bits = bits;
    _sign = sign ? MINUS : PLUS;
    Normalize();
}

InfiniteInt::InfiniteInt(vector<long long> bits, unsigned int sign) {
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

    long long carry, tmp, digit;

    for (long i = 0; i < num.size(); i++) {
        carry = num[i] - '0';

        for (signed long j = _bits.size() - 1; j >= 0; j--) {
            digit = _bits[j];
            tmp = digit * 10 + carry;
            _bits[j] = tmp % ((long long)MaxInt);
            carry = tmp / ((long long)MaxInt);
        }

        if (carry)
            _bits.insert(_bits.begin(), carry);
    }



    this->Normalize();
    std::reverse(this->_bits.begin(), this->_bits.end());
}

const bool InfiniteInt::operator==(InfiniteInt num) {
    return _sign == num._sign && _bits == num._bits;
}

const bool InfiniteInt::operator<=(InfiniteInt num) {
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

        return f;
    }
}

const bool InfiniteInt::operator<(InfiniteInt num) {
    return *this <= num && !(*this == num);
}

const bool InfiniteInt::operator>=(InfiniteInt num) {
    return *this > num || *this == num;
}

const bool InfiniteInt::operator>(InfiniteInt num) {
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
        long long tmp = 0;

        for (int i = 0; i < min_length; i++) {
            tmp = (long long)_bits[i] + (long long)num._bits[i] + (long long)carry;
            carry = tmp / MaxInt;
            res[i] = tmp % MaxInt;
        }
        for (unsigned long i = min_length; i < res.capacity() - 1; i++) {
            tmp = (long long)(k > l ? _bits[i] : num._bits[i]) + (long long)carry;
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
            minuend = _bits;
            substrahend = num._bits;
        }
        else {
            sign = 1;
            res.resize(l, 0);
            minuend = num._bits;
            substrahend = _bits;
        }

        unsigned long min_length = k > l ? l : k;
        int carry = 0;
        long long tmp = 0;

        for (int i = 0; i < min_length; i++) {
            tmp = (long)minuend[i] - (long)substrahend[i] + (long)carry;
            if (tmp >= 0)
                carry = (tmp / MaxInt);
            else {
                carry = -1;
                tmp += ((long long)1 << 32);
            }
            res[i] = tmp % MaxInt;
        }
        for (unsigned long i = min_length; i < res.capacity(); i++) {
            tmp = (long)minuend[i] + (long)carry;
            if (tmp >= 0)
                carry = tmp / MaxInt;
            else {
                carry = -1;
                tmp += ((long long)1 << 32);
            }
            res[i] = tmp % MaxInt;
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
    __int128 tmp = 0;

    for (int i = 0; i < k + l; i++)
        res[i] = 0;

    for (int i = 0; i < k; i++) {
        carry = 0;
        for (int j = 0; j < l; j++) {
            tmp = (__int128)_bits[i] * (__int128)num._bits[j] + (__int128)res[i + j]
                  + (__int128)carry;
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

    /*InfiniteInt res;
    InfiniteInt curValue;
    res._bits.resize(_bits.capacity() + num._bits.capacity(), 0);
    curValue._bits.resize(_bits.capacity() + num._bits.capacity(), 0);

    unsigned long k = _bits.capacity();
    unsigned long l = num._bits.capacity();

    for (long i = k - 1; i >= 0; i--)
    {
        curValue.LevelUp(); // * 2^N
        curValue._bits[0] = _bits[i];

        // подбираем максимальное число x, такое что num * x <= curValue
        unsigned long x = 0;
        unsigned long s = 0, r = (unsigned long)1 << B;

        while (s <= r)
        {
            unsigned long m = (s + r) >> 1;
            InfiniteInt cur = num * InfiniteInt(m, 0);
            if (cur <= curValue)
            {
                x = m;
                s = m + 1;
            }
            else
                r = m - 1;
        }
        res._bits[i] = x;
        InfiniteInt numx = num*x;
        curValue = curValue - numx;
    }

    // избавляемся от лидирующих нулей
    res.Normalize();
    */

    return QuoRem(*this, num).first;

}

InfiniteInt InfiniteInt::operator/=(InfiniteInt num) {
    *this = *this / num;
    return *this;
}

InfiniteInt InfiniteInt::operator%(InfiniteInt num) {

    /*InfiniteInt res;
    InfiniteInt curValue;
    res._bits.resize(_bits.capacity() + num._bits.capacity(), 0);
    curValue._bits.resize(_bits.capacity() + num._bits.capacity(), 0);

    unsigned long k = _bits.capacity();
    unsigned long l = num._bits.capacity();

    for (long i = k - 1; i >= 0; i--)
    {
        curValue.LevelUp(); // * 2^N
        curValue._bits[0] = _bits[i];

        // подбираем максимальное число x, такое что num * x <= curValue
        unsigned long x = 0;
        unsigned long s = 0, r = (unsigned long)1 << B;

        while (s <= r)
        {
            unsigned long m = (s + r) >> 1;
            InfiniteInt cur = num * InfiniteInt(m, 0);
            if (cur <= curValue)
            {
                x = m;
                s = m + 1;
            }
            else
                r = m - 1;
        }
        res._bits[i] = x;
        InfiniteInt numx = num*x;
        curValue = curValue - numx;
    }

    // избавляемся от лидирующих нулей
    res.Normalize();
    */

    return QuoRem(*this, num).second;
}

InfiniteInt InfiniteInt::operator<<(unsigned int deg) {
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

    return res;
}

void InfiniteInt::LevelUp() {
    unsigned long len = _bits.capacity();
    _bits.resize(len + 1);
    for (unsigned long i = len; i >= 1; i--)
        _bits[i] = _bits[i - 1];
    _bits[0] = 0;
    this->Normalize();
}

void InfiniteInt::Normalize() {
    unsigned long l = _bits.capacity();
    for (unsigned long i = l - 1; i > 0 && _bits[i] == 0; i--)
        _bits.resize(i);
    _bits.shrink_to_fit();
}

string InfiniteInt::BigIntToDecimalString(unsigned int _base) {
    string res = "";
    InfiniteInt base(_base, 0);
    InfiniteInt tmp(this->_bits, this->_sign);
    for (; tmp._bits.size() > 1 || tmp._bits[0] > 0;) {
        res = std::to_string((tmp % base).getBits()[0]) + res;
        tmp = tmp / base;
    }

    return res;
}

vector<unsigned int> InfiniteInt::getBits() {
    return _bits;
}

pair<long long, long long> correctDivMod(__int128 a, __int128 b) {
    long long q = a / b;
    long long r = a % b;
    if (a >= 0 && b >= 0 || a <= 0 && b <= 0)
        return make_pair(q, r);
    else
        return make_pair(q - 1, r + b);
};

pair<InfiniteInt, InfiniteInt> InfiniteInt::QuoRem(InfiniteInt d_dent, InfiniteInt d_der) {
    int w = 0;
    InfiniteInt divident = d_dent;
    InfiniteInt divider = d_der;
    unsigned long lenDivider = divider._bits.size();
    while (divider._bits[divider._bits.capacity() - 1] < MaxInt/2) {
        divident <<= 1;
        divider <<= 1;
        w++;
    }


    vector<long long> quot;
    vector<long long> rem;

    unsigned long k = divident._bits.capacity();
    unsigned long l = divider._bits.capacity();

    rem.resize(k > l ? k + 1 : l + 1, 0);
    quot.resize(k - l + 1, 0);

    long long carry = 0;
    __int128 tmp = 0;

    for (int i = 0; i < k; i++)
        rem[i] = divident._bits[i];

    for (long long i = k - l; i >= 0; i--) {
        tmp = ( ((__int128) rem[i + l]) << 32) | (__int128) rem[i + l - 1];
        carry = divider._bits[l - 1];
        bool ff = tmp > carry;
        quot[i] = tmp / carry;

        if (quot[i] >= MaxInt)
            quot[i] = MaxInt - 1;
        carry = 0;

        for (int j = 0; j < l; j++) {
            tmp = (__int128)rem[i + j] - (__int128)quot[i] * (__int128)divider._bits[j] + (__int128)carry;
            bool f = tmp < 0;
            f = abs(tmp) - MaxInt > 0;
            std::tie(carry, rem[i+j]) = correctDivMod(tmp, (__int128)MaxInt);
            if (rem[i+j] < 0) rem[i+j] *= -1;
            if (lenDivider == 1) carry++;
            //carry = tmp / (__int128)MaxInt;
            //rem[i+j] = abs(tmp % (__int128)MaxInt);
        }

        if (rem[i + l] != 0) rem[i + l] = rem[i + l] + carry;

        for (; rem[i + l] < 0;) {
            carry = 0;
            for (int j = 0; j < l; j++) {
                tmp = (__int128)rem[i + j] + (__int128)divider._bits[j] + (__int128)carry;
                std::tie(carry, rem[i+j]) = correctDivMod(tmp, (__int128)MaxInt);
                if (rem[i+j] < 0) rem[i+j] *= -1;
                if (lenDivider == 1) carry++;
                //carry = tmp / (__int128)MaxInt;
                //rem[i+j] = abs(tmp % (__int128)MaxInt);
            }
            rem[i + l] += carry;
            quot[i]--;
        }
    }


    InfiniteInt quo(quot, divident._sign ^ divider._sign);
    InfiniteInt re(rem, 0);

    quo.Normalize();
    re.Normalize();

    re >>= w;

    if (re == d_der) {
        re = 0;
        quo += 1;
    }
    return make_pair(quo, re);

}

unsigned int InfiniteInt::operator[](long long i) {
    return this->_bits[i];
}


InfiniteInt InfiniteInt::operator<<=(unsigned int deg) {
    return (*this = *this << deg);
}

InfiniteInt InfiniteInt::operator>>=(unsigned int deg) {
    return (*this = *this >> deg);
}

std::pair<InfiniteInt, InfiniteInt> InfiniteInt::NewQuoRem(const InfiniteInt &lhs, const InfiniteInt &rhs) {
    if (rhs._bits.size() == 1 && rhs._bits[0] == 0) {
        cout << "Division by zero" << endl;
        return std::make_pair(lhs, 0);
    }
    InfiniteInt dividend = lhs;
    InfiniteInt divisor = rhs;

    bool negative = 0;
    if (dividend < 0) {
        negative = !negative;
        dividend._sign = PLUS;
    }
    if (divisor < 0) {
        negative = !negative;
        divisor._sign = PLUS;
    }

    InfiniteInt remainder = 0;
    InfiniteInt quotient = 0;
    while (dividend._bits.size() > 0) {
        remainder._bits.insert(remainder._bits.begin(), dividend._bits[dividend._bits.size() - 1]);
        remainder._bits.push_back(0);
        remainder.Normalize();
        dividend._bits.pop_back();

        if (divisor > remainder) {
            quotient._bits.push_back(0);
        } else {
            int count = 0;
            long i = divisor._bits.size() - 1;
            InfiniteInt value = 0;
            while (i > 0) {
                InfiniteInt increase = divisor * i;
                InfiniteInt next = value + increase;
                if (next <= remainder) {
                    value = next;
                    count += i;
                }
                i >>= 1;
            }
            quotient._bits.push_back(count);
            remainder -= value;
        }
    }

    for (int i = 0; i < quotient._bits.size() / 2; i++) {
        unsigned int swap = quotient._bits[i];
        quotient._bits[i] = quotient._bits[(quotient._bits.size() - 1) - i];
        quotient._bits[quotient._bits.size() - 1 - i] = swap;
    }

    if (negative) quotient._sign = (quotient._sign) ? PLUS : MINUS;
    if (negative) remainder._sign = (remainder._sign) ? PLUS : MINUS;
    quotient.Normalize();
    remainder.Normalize();
    return std::make_pair(quotient, remainder);
}


