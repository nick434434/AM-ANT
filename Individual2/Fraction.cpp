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


void reduceFraction(Iint& t, Iint& s) {
    Iint d = gcd(t, s);
    if ( !(d == 1) )
        t /= d, s /= d;
}

void makeMostCloser(Iint& t, Iint& s, const Iint ratio) {
    Iint tmp = t / s;
    bool f = tmp > ratio;
    if (f)
        while (f) {
            t -= 1;
            tmp = t / s;
            f = tmp > ratio;
            if (f) {
                s += 1;
                tmp = t / s;
                f = tmp > ratio;
            }
        }
    else if (tmp < ratio) {
        f = true;
        while (f) {
            t += 1;
            tmp = t / s;
            f = tmp < ratio;
            if (f) {
                s > 1 ? s -= 1 : t += 1;
                tmp = t / s;
                f = tmp > ratio;
            }
        }
    }
}

//Shitty of course
///TARGET FUNCTION
/// \param fr
Fraction::Fraction(DecFr fr) {

    if (fr.size() == 1) {
        s = fr[0];
        t = 10;
        M = 2;
        reduceFraction(t, s);
        return;
    }
    else if (fr.size() == 2) {
        s = fr[0]*10 + fr[1];
        Iint s0 = s;
        t = 100;
        M = 7;
        reduceFraction(t, s);
        while (t > M) {
            t % 2 == 0 ? t -= 2 : t -= 3;
            if (s > 1)
                s -= 1;
            reduceFraction(t, s);
        }
    }
    else {
        t = Fraction::tenInDegree(fr.size());
        s = 0;
        M = (t >> 1).sqrt();
        Iint pow10 = 1;
        for (size_t i = 0; i < fr.size(); i++) {
            s += pow10 * fr[fr.size() - i - 1];
            pow10 *= 10;
        }

        const Iint ratio0 = t / s;

        bool f = false;
        if (ratio0 > M) {
            t = ratio0;
            s = 1;
        }
        else {
            f = true;
            s = t - s;
            t *= t;
            t /= 10;
        }

        if (t > M) {
            if (f) {
                s *= Fraction::tenInDegree(fr.size() - 1);
                s = t - s;
                reduceFraction(t, s);
            }

            while (t > M) {
                if (s == 1) {
                    t = ratio0;
                    break;
                }
                if (t % 2 == 0)
                    t -= 4;
                else
                    t -= 3;
                s -= 1;
                reduceFraction(t, s);
            }
        } else {
            Iint ratio = M / t;
            t *= ratio + 1;
            s *= ratio + 1;

            Iint ss = s - 1, tt = t - 1;
            while (t > M && (!(ss == s && tt == t))) {
                ss = s;
                tt = t;

                Iint tmp = t - s;
                s = tmp / ratio0;
                t = tmp;

                makeMostCloser(t, s, ratio0);

                reduceFraction(t, s);
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

string Fraction::get_S_and_T() {
    return s.BigIntToDecimalString() + ';' + t.BigIntToDecimalString() + ';';
}


