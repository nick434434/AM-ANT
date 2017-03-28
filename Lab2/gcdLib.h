//
// Created by Никита Ковалев on 27.03.2017.
//

#ifndef LAB2_GCDLIB_H
#define LAB2_GCDLIB_H


#include "InfiniteInt.h"


using std::pair;


InfiniteInt gcd(const InfiniteInt a, const InfiniteInt b);

InfiniteInt lcm(const InfiniteInt a, const InfiniteInt b);

InfiniteInt binaryGcd(const InfiniteInt a, const InfiniteInt b);

pair<InfiniteInt, pair<InfiniteInt, InfiniteInt>> extGcd(const InfiniteInt a, const InfiniteInt b);

pair<InfiniteInt, pair<InfiniteInt, InfiniteInt>> extBinGcd(const InfiniteInt a, const InfiniteInt b);


#endif //LAB2_GCDLIB_H
