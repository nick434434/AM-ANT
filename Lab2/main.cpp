

#include <iostream>
#include "gcdLib.h"


using std::cout;
using std::endl;


int main() {

    pair<InfiniteInt, pair<InfiniteInt, InfiniteInt>> res = extGcd(64, 13);

    cout << res.first.BigIntToDecimalString() << endl << res.second.first.BigIntToDecimalString() << " "
         << res.second.second.BigIntToDecimalString() << endl;

    return 0;
}