#include <iostream>
#include <cstdlib> // za rand()
#include <cmath>
#include <algorithm>

using namespace std;

// Func za modular multiplication (a * b) % mod, neka nema overflow
long long mulmod(long long a, long long b, long long mod) {
    long long res = 0;
    a %= mod;
    while (b > 0) {
        if (b % 2 == 1) res = (res + a) % mod;
        a = (a * 2) % mod;
        b /= 2;
    }
    return res;
}
//exp e exponent/stepen
// Func za modular exponentiation (base^exp) % mod
long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = mulmod(res, base, mod); // neka mulmod za da nemat overflow
        base = mulmod(base, base, mod);
        exp /= 2;
    }
    return res;
}

// Miller-Rabin primality test, k iterations za *accuracy*
bool millerTest(long long n, int k) {
    if (n < 2) return false;
    if (n != 2 && n % 2 == 0) return false;

    long long d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }

    for (int i = 0; i < k; i++) {
        // deterministic witnesses moit za mali brojki
        // za ostanato neka probabilistic use, a random 'a' in [2, n-2]
        long long a = 2 + rand() % (n - 3); 
        long long x = power(a, d, n);

        if (x == 1 || x == n - 1) continue;

        bool composite = true;
        long long temp = d;
        while (temp != n - 1) {
            x = mulmod(x, x, n);
            temp *= 2;
            if (x == 1) return false; // Definitely composite (composite e kvadrat pr. 2^2 = 4, 4 e comp)
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false; // Definitely composite
    }
    return true; // Valda e prime
}


int main() {
    int iterations = 5; // poike iterations za poike accuracy
    long long num;
    cout << "Enter integer to test primality: ";
    cin >> num;
    if (millerTest(num, iterations))
        cout << num << " is probably prime" << endl;
    else
        cout << num << " is composite" << endl;
    return 0;
}
