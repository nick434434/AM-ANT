
#include <iostream>
#include "Fraction.h"


using std::cout;
using std::cin;
using std::endl;


int main() {

    Fraction f(34, 27);

    cout << f << endl;

    DecFr fr(cout, cin);

    cout << fr << endl;

    Fraction f1(fr);

    cout << f1 << endl;

    return 0;
}