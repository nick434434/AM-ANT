//
// Created by Никита Ковалев on 27.03.2017.
//


#include "gcdLib.h"
#include <sstream>
#include <cstdlib>
#include <tuple>


using std::make_pair;
using std::stringstream;


///ADDITIONAL FUNCTIONS
bool isEven(const InfiniteInt a) {
    return InfiniteInt(a) % 2 == 0;
}

void swapWithQuotient(InfiniteInt& a, InfiniteInt& b, const InfiniteInt q) {
    InfiniteInt t = b;
    b = InfiniteInt(q)*t;
    b = a - b;
    a = t;
}

string randNum(const unsigned int len) {

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
///


///TASK FUNCTIONS
InfiniteInt gcd(const InfiniteInt a, const InfiniteInt b) {
    InfiniteInt aa = a;
    InfiniteInt bb = b;
    InfiniteInt t;
    while (!(bb == 0)) {
        t = bb;
        bb = aa % bb;
        aa = t;
    }
    return aa;
}

InfiniteInt lcm(const InfiniteInt a, const InfiniteInt b) {
    InfiniteInt aa = a;
    InfiniteInt bb = b;

    if (aa > bb)
        aa /= gcd(aa, bb);
    else
        bb /= gcd(aa, bb);
    aa *= bb;

    return aa;
}

InfiniteInt binaryGcd(const InfiniteInt a, const InfiniteInt b) {
    InfiniteInt aa = a;
    InfiniteInt bb = b;

    if (aa == 0)
        return b;
    if (bb == 0)
        return a;

    uint64_t pow2 = 0;

    while ( isEven(aa) && isEven(bb) ) {
        pow2++;
        aa /= 2;
        bb /= 2;
    }

    while ( isEven(aa) ) aa /= 2;

    while ( isEven(bb) ) bb /= 2;

    while ( !(bb == 0) ) {
        if (aa > bb) {
            InfiniteInt t = aa;
            aa = bb;
            bb = t;
        }
        bb -= aa;
    }

    return aa <<= pow2;

}

pair<InfiniteInt, pair<InfiniteInt, InfiniteInt>> extGcd(const InfiniteInt a, const InfiniteInt b) {
    InfiniteInt aa = a, bb = b;

    if ( aa == 0 )
        return make_pair(bb, make_pair(0, 1));
    if ( bb == 0 )
        return make_pair(aa, make_pair(1, 0));

    InfiniteInt u = 0, u0 = 1;
    InfiniteInt v = 1, v0 = 0;
    InfiniteInt q, rem;
    while ( !(bb == 0) ) {
        std::tie(q, rem) = aa.QuoRem(aa, bb);
        aa = bb;
        bb = rem;
        swapWithQuotient(u0, u, q);
        swapWithQuotient(v0, v, q);
    }

    return make_pair(aa, make_pair(u0, v0));
}

pair<InfiniteInt, pair<InfiniteInt, InfiniteInt>> extBinGcd(const InfiniteInt a, const InfiniteInt b) {
    InfiniteInt aa(InfiniteInt(a).getBits(), 0), bb(InfiniteInt(b).getBits(), 0);

    if ( aa == 0 )
        return make_pair(bb, make_pair(0, 1));
    if ( bb == 0 )
        return make_pair(aa, make_pair(1, 0));

    InfiniteInt u = 1, v = 0, s = 0, t = 1;
    uint64_t pow2 = 0;
    while ( isEven(aa) && isEven(bb) ) {
        pow2++;
        aa /= 2;
        bb /= 2;
    }

    const InfiniteInt alpha = aa, beta = bb;
    while ( isEven(aa) ) {
        aa /= 2;
        if ( isEven(u) && isEven(v) ) {
            u /= 2;
            v /= 2;
        }
        else {
            u = (u + beta) / 2;
            v = (v - alpha) / 2;
        }
    }

    while ( !(aa == bb) ) {
        if ( isEven(bb) ) {
            bb /= 2;
            if ( isEven(s) && isEven(t) ) {
                s /= 2;
                t /= 2;
            }
            else {
                s = (s + beta) / 2;
                t = (t - alpha) / 2;
            }
        }
        else if (bb < aa) {
            swapWithQuotient(aa, bb, 0);
            swapWithQuotient(u, s, 0);
            swapWithQuotient(v, t, 0);
        }
        else {
            bb -= aa;
            s -= u;
            t -= v;
        }
    }

    InfiniteInt gcd = aa << pow2;

    if ( !(gcd == s*InfiniteInt(a) + t*InfiniteInt(b)) ) {
        if (gcd == s*InfiniteInt(a) - t*InfiniteInt(b))
            return make_pair(gcd, make_pair(s, t*(-1)));
        if (gcd == s*InfiniteInt(a)*(-1) + t*InfiniteInt(b))
            return make_pair(gcd, make_pair(s*(-1), t));
        if (gcd == s*InfiniteInt(a)*(-1) - t*InfiniteInt(b))
            return make_pair(gcd, make_pair(s*(-1), t*(-1)));
    }


    return make_pair(gcd, make_pair(s, t));
}
///


///TESTS
bool makeTestsExtGcd() {

    string v1 = randNum(10);
    string v2 = randNum(5);
    bool f = true;
    for (unsigned int i = 10; i < 201 & f; i++) {
        InfiniteInt a(v1, 0);
        InfiniteInt b(v2, 0);
        pair<InfiniteInt, pair<InfiniteInt, InfiniteInt>> c = extGcd(a, b);
        InfiniteInt d = c.second.first*a + c.second.second*b;
        f = c.first == d;
        v1 = randNum(i + 1);
        v2 = randNum(i - 4);
    }

    return f;

}

bool makeTestsGcd() {

    string v1 = randNum(20);
    string v2 = randNum(15);
    bool f = true;
    for (unsigned long i = 20; i < 41 & f; i++) {

        InfiniteInt a(v1, 0);
        InfiniteInt b(v2, 0);
        InfiniteInt c = gcd(a, b);
        f = false;
        if (a % c == 0 && b % c == 0 ) {
            a /= c;
            b /= c;
            if (gcd(a, b) == 1)
                f = true;
        }

        v1 = randNum(i);
        v2 = randNum(i - 5);
    }


    return f;

}

bool makeTestsLcm() {

    string v1 = randNum(20);
    string v2 = randNum(15);
    bool f = true;
    for (unsigned long i = 20; i < 41 & f; i++) {

        InfiniteInt a(v1, 0);
        InfiniteInt b(v2, 0);
        InfiniteInt c = lcm(a, b);
        a = c / a;
        b = c / b;
        if (gcd(a, b) == 1)
            f = true;

        v1 = randNum(i + 1);
        v2 = randNum(i - 4);
    }


    return f;

}

bool makeTestsBinGcd() {

    string v1 = randNum(20);
    string v2 = randNum(15);
    bool f = true;
    for (unsigned int i = 20; i < 41 & f; i++) {

        InfiniteInt a(v1, 0);
        InfiniteInt b(v2, 0);
        InfiniteInt c = binaryGcd(a, b);
        f = false;
        if (a % c == 0 && b % c == 0 ) {
            a /= c;
            b /= c;
            if (gcd(a, b) == 1)
                f = true;
        }

        wprintf(L"%u ", i);

        v1 = randNum(i + 1);
        v2 = randNum(i - 4);
    }


    return f;

}

bool testSwap(InfiniteInt quot) {

    string v1 = randNum(20);
    string v2 = randNum(15);
    bool f = true;
    for (unsigned long i = 20; i < 1000 & f; i++) {

        InfiniteInt a(v1, 0), a0(v1, 0);
        InfiniteInt b(v2, 0), b0(v2, 0);
        InfiniteInt c = a - quot*b;
        swapWithQuotient(a0, b0, quot);
        f = c == b0;

        v1 = randNum(i + 1);
        v2 = randNum(i - 4);
    }


    return f;

}
///