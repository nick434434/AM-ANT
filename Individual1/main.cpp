#include <iostream>
#include <mpir.h>
#include <mpirxx.h>
#include <iomanip>
#include "getCPUTime.h"
#include <fstream>

using std::ostream;
using std::ofstream;
using std::cout;
using std::endl;
using std::setw;

/*
 *  Basic combinatorial functions
 */
mpz_class binomial(unsigned int n, unsigned int k) {

    if (k > n)
        return 0;
    else {
        if (k > n - k)
            k = n - k;

        mpz_class res = 1;
        for (size_t i = n; i > n - k; i--)
            res *= i;
        for (size_t i = 1; i < k + 1; i++)
            res /= i;

        return res;
    }
}

mpz_class fact(unsigned int n) {
    mpz_class res = 1;
    for (int i = 2; i < n + 1; i++)
        res *= i;

    return res;
}

mpz_class multipleTwoBinomials(unsigned int n, unsigned int k1, unsigned int k2) {

    if (k1 > n || k2 > n)
        return 0;
    else {
        if (k1 > n - k1)
            k1 = n - k1;
        if (k2 > n - k2)
            k2 = n - k2;

        mpz_class res = 1;

        unsigned int k = (k1 > k2) ? k1 : k2;
        unsigned int kk = (k1 > k2) ? k2 : k1;

        for (int i = n - kk + 1; i <= n; i++)
            res *= i * i;
        for (int i = n - kk; i > (int) n - (int) k; i--)
            res *= i;

        res /= fact(k);
        res /= fact(kk);

        return res;
    }
}


/*
 *  Functions for Narayana numbers, both direct and optimized
 */
mpz_class numNarayana(unsigned int n, unsigned int k) {
    return binomial(n, k)*binomial(n, k-1)/(mpz_class)n;
}

mpz_class numNarayanaOptimized(unsigned int n, unsigned int k) {
    return multipleTwoBinomials(n, k, k - 1)/(mpz_class)n;
}

mpz_class sumNarayana(unsigned int n) {
    mpz_class res = 0;
    for (size_t i = 1; i <= n; i++)
        res += numNarayana(n, i);

    return res;
}


/*
 *  Functions for Catalan numbers, 3 various approaches
 */
mpz_class binomCatalan(unsigned int n) {
    return binomial(2*n, n)/(mpz_class)(n + 1);
}

mpz_class factCatalan(unsigned int n) {
    mpz_class res = 1;
    for (int i = n + 2; i < 2*n + 1; i++)
        res *= i;

    res /= fact(n);

    return res;
}

mpz_class multipCatalan(unsigned int n) {
    mpz_class res = 1;
    for (int i = 2; i < n + 1; i++)
        res *= (n + i);
    for (int i = 2; i < n + 1; i++)
        res /= i;

    return res;
}


/*
 *  Functions for printing Narayana and Catalan numbers, using different approaches and showing computation time
 */
void printNarayana(unsigned int n, ostream& output = cout) {
    mpz_class tmp = 0;
    double start, end;


    if (output == cout)
        for (size_t i = 1; i <= n; i++) {
            output << setw(3) << i;
            start = getCPUTime();
            tmp = numNarayana(n, i);
            end = getCPUTime();
            output << setw(20) << tmp << " " << std::setprecision(10) << std::fixed << end - start << endl;

            start = getCPUTime();
            tmp = numNarayanaOptimized(n, i);
            end = getCPUTime();
            output << setw(23) << tmp << " " << std::setprecision(10) << std::fixed << end - start << endl;

        }
    else
        for (size_t i = 1; i <= n; i++) {
            output << i << ";";
            start = getCPUTime();
            tmp = numNarayana(i, i/2 + 1);
            end = getCPUTime();
            output << tmp << ";" << std::setprecision(10) << std::fixed << end - start << ";";

            start = getCPUTime();
            tmp = numNarayanaOptimized(i, i/2 + 1);
            end = getCPUTime();
            output << std::setprecision(10) << std::fixed << end - start << endl;

            if (i%1000 == 0)
                cout << i << endl;
        }
}

void printCatalan(unsigned int n, ostream& output = cout) {
    mpz_class tmp = 0;
    double start, end;

    if (output == cout)
        for (size_t i = 1; i <= n; i++) {
            cout << setw(3) << i;
            start = getCPUTime();
            tmp = binomCatalan(i);
            end = getCPUTime();
            cout << setw(20) << tmp << " " << std::setprecision(10) << std::fixed << end - start << endl;

            start = getCPUTime();
            tmp = factCatalan(i);
            end = getCPUTime();
            cout << setw(23) << tmp << " " << std::setprecision(10) << std::fixed << end - start << endl;

            start = getCPUTime();
            tmp = multipCatalan(i);
            end = getCPUTime();
            cout << setw(23) << tmp << " " << std::setprecision(10) << std::fixed << end - start << endl;
        }
    else
        for (size_t i = 1; i <= n; i++) {
            output << i << ";";
            start = getCPUTime();
            tmp = binomCatalan(i);
            end = getCPUTime();
            output << tmp << ";" << std::setprecision(10) << std::fixed << end - start << ";";

            start = getCPUTime();
            tmp = factCatalan(i);
            end = getCPUTime();
            output << std::setprecision(10) << std::fixed << end - start << ";";

            start = getCPUTime();
            tmp = multipCatalan(i);
            end = getCPUTime();
            output << std::setprecision(10) << std::fixed << end - start << endl;
        }
}


/*
 *  Check if sum of a row of Narayana numbers equals respective Catalan number
 */
bool checkIfEqual(unsigned int n) {

    mpz_class sum = 0;
    for (size_t i = 1; i <= n; i++)
        sum += numNarayanaOptimized(n, i);

    return sum == factCatalan(n);
}


/*
 *  Target functions that print a triangle/row/column of Narayana numbers or a single number, based on parameters (n, k)
 */
void printTriangleNarayana(unsigned int n, int width) {

    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= i; j++)
            cout << setw(width) << numNarayanaOptimized(i, j) << " ";
        cout << endl;
    }

}

void printRowNaryana(unsigned int n, int width) {

    for (size_t i = 1; i <= n; i++)
        cout << setw(width) << numNarayanaOptimized(n, i) << " ";
    cout << endl;

}

void printColumnNarayana(unsigned int col, unsigned int n, int width) {

    for (size_t i = col; i <= n; i++)
        cout << setw(width) << numNarayanaOptimized(i, col) << endl;
    cout << endl;

}

void printNumNarayana(unsigned int n, unsigned int k) {
    cout << numNarayana(n, k) << endl;
}


int main() {
    cout << endl;

    
    bool f = true;
    size_t i = 1;
    for (i = 1; i <= 40 && f; i++)
        f &= checkIfEqual(i);
    cout << "Catalan and rows of Narayana numbers are " << (f ? "equal" : "not equal")  << endl;
    cout << endl;
    cout << endl;


    printNarayana(20);
    cout << endl;
    cout << endl;



/*
///making source files for plots
///
    ofstream fout("outNarayana5000.csv");
    printNarayana(5000, fout);

    fout.close();
    fout.open("outCatalan5000.csv");
    printCatalan(5000, fout);
///
*/
    printColumnNarayana(5, 20, 15);

    printTriangleNarayana(20, 15);

    return 0;
}