//
// Created by Никита Ковалев on 01.04.2017.
//

#include "Fraction.h"
#include <iostream>
#include <cmath>
#include "gcdLib.h"

using std::cout;
using std::endl;
using std::cin;


//Shitty of course
///TARGET FUNCTION
/// \param fr
Fraction::Fraction(DecFr fr) {
    t = Fraction::tenInDegree(fr.size());
    s = 0;
    M = (t >> 1).sqrt();
    Iint pow10 = 1;
    for (size_t i = 0; i < fr.size(); i++) {
        s += pow10*fr[fr.size() - i - 1];
        pow10 *= 10;
    }
    Iint ratio = t / s;

    Iint d;
    if ( !((d = gcd(s, t)) == 1) ) {
        s /= d;
        t /= d;
    }

    while ( t >= M ) {
        while ( t % 2 == 0 && s % 2 == 0 ) t >>= 1, s >>= 1;

        Iint tmp = t - s;
        t = tmp;
        s = tmp / ratio;

        bool f = (t / s) < ratio;
        if ( f )
            while (f) {
                t += 1, f = (t / s) < ratio;
                if (f)
                    s -= 1;
            }
        else {
            bool f1 = true;
            while (f1) {
                t -= 1, f1 = (t / s) > ratio;
                if (f1)
                    s += 1;
            }
        }
    }

}
///


std::ostream &operator<<(std::ostream &os, const Fraction &obj) {
    cout << obj.s << '/' << obj.t << endl << "M = " << obj.M;
    return os;
}

Iint Fraction::tenInDegree(uint64_t k) {
    Iint res = 1;
    for (size_t i = 0; i < k; i++)
        res *= 10;
    return res;
}


