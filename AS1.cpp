#include <iostream>
#include <chrono>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

void single_thread_sieve(ofstream &myfile);

int main()
{
    ofstream myfile;
    myfile.open("primes.txt");
    auto start = std::chrono::high_resolution_clock::now();

    single_thread_sieve(myfile);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " milliseconds" << endl;
}

void single_thread_sieve(ofstream &myfile)
{
    // normal sieve of eratosthenes
    int n = 100000000;
    int *prime = new int[n + 1];
    for (int i = 0; i <= n; i++)
        prime[i] = 1;
    prime[0] = 0;
    prime[1] = 0;
    for (int i = 2; i * i <= n; i++)
    {
        if (prime[i] == 1)
        {
            for (int j = i * i; j <= n; j += i)
                prime[j] = 0;
        }
    }

    //print last 10 primes
    int prime_count = 0;
    long int sum = 0;
    vector<long int> list;
    for (int i = n; i >= 0; i--)
    {
        if (prime[i] == 1)
        {
            prime_count++;
            sum += i;
            if (prime_count <= 10)
                list.insert(list.begin(), i);
        }
    }

    list.insert(list.begin(), sum);
    list.insert(list.begin(), prime_count);
    for (int i = 0; i < list.size(); i++)
    {
        myfile << list[i] << '   ';
    }
}