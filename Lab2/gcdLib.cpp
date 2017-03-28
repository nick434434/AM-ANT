//
// Created by Никита Ковалев on 27.03.2017.
//


#include "gcdLib.h"


using std::make_pair;


bool isEven(const InfiniteInt a) {
    return InfiniteInt(a) % 2 == 0;
}

void swapWithQuotient(InfiniteInt& a, InfiniteInt& b, const InfiniteInt q) {
    InfiniteInt t = b;
    b = a - InfiniteInt(q)*t;
    a = t;
}


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
        aa >>= 1;
        bb >>= 1;
    }

    while ( isEven(aa) ) aa >>= 1;

    while ( isEven(bb) ) bb >>= 1;

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
    InfiniteInt aa = a;
    InfiniteInt bb = b;

    if ( aa == 0 )
        return make_pair(bb, make_pair(0, 1));
    if ( bb == 0 )
        return make_pair(aa, make_pair(1, 0));

    InfiniteInt u = 0, u0 = 1;
    InfiniteInt v = 1, v0 = 0;
    InfiniteInt r = bb, r0 = aa;
    InfiniteInt q;
    while ( !(r == 0) ) {
        q = r0 / r;
        swapWithQuotient(r0, r, q);
        swapWithQuotient(u0, u, q);
        swapWithQuotient(v0, v, q);
    }


    return make_pair(r0, make_pair(u0, v0));
}

pair<InfiniteInt, pair<InfiniteInt, InfiniteInt>> extBinGcd(const InfiniteInt a, const InfiniteInt b) {
    return pair<InfiniteInt, pair<InfiniteInt, InfiniteInt>>();
}
