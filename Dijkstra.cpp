#include <iostream>
#include <vector>
#include <set>
#include <numeric>

using namespace std;

void dijkstraPrimes(int limit) {
    // cuva prime najdeni
    vector<int> primes; 
    // cuva parovi (next multiple, prime od nego), ordered by multiple
    set<pair<int, int>> multiples_pool; 

    if (limit >= 2) {
        primes.push_back(2);
        multiples_pool.insert({4, 2}); // Start so 2*2
    }

    for (int n = 3; n <= limit; ++n) {
        // duri najmal  multiple >n, inkrimentinraj
        while (!multiples_pool.empty() && multiples_pool.begin()->first < n) {
            pair<int, int> smallest = *multiples_pool.begin();
            multiples_pool.erase(multiples_pool.begin());
            // Inkrimet multiple za prime
            multiples_pool.insert({smallest.first + smallest.second, smallest.second}); 
        }

        // dali multiple E?
        if (!multiples_pool.empty() && multiples_pool.begin()->first == n) {
            // n= multiple, n ne= prime. Update multiple.
            pair<int, int> smallest = *multiples_pool.begin();
            multiples_pool.erase(multiples_pool.begin());
            multiples_pool.insert({smallest.first + smallest.second, smallest.second});
        } else {
            // n = prime, add to list and its square to the pool
            primes.push_back(n);
            // optimizacija: samo dodaj multiples >= n*n vo pool
            // No overflow if n*n is too large for int
            if ((long long)n * n <= limit) {
                multiples_pool.insert({n * n, n});
            }
        }
    }

    cout << "Primes up to " << limit << " are: ";
    for (int p : primes) {
        cout << p << " ";
    }
    cout << endl;
}

int main() {
    dijkstraPrimes(100);
    return 0;
}
