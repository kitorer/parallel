#include <iostream>
#include <chrono>
#include <fstream>
#include <bits/stdc++.h>
#include <thread>
#include <mutex>
#include <algorithm>

using namespace std;

void single_thread_sieve(ofstream &myfile);
void multi_thread_sieve(ofstream &myfile);

int main()
{
    ofstream myfile;
    myfile.open("primes.txt");
    
    multi_thread_sieve(myfile);
    single_thread_sieve(myfile);

    myfile.close();
}

void multi_thread_sieve(ofstream &myfile)
{
    auto start = std::chrono::high_resolution_clock::now();

    int n = 100000000;
    int *prime = new int[n + 1];
    for (int i = 0; i <= n; i++)
        prime[i] = 1;
    prime[0] = 0;
    prime[1] = 0;

    int num_threads = 8;
    int range = n / num_threads;
    vector<thread> threads;
    for (int i = 0; i < num_threads; i++)
    {
        int start = i * range;
        int end = (i + 1) * range;
        cout<< start << " " << end << endl;
        threads.push_back(thread([=] {
            for (int j = 2; j * j <= end; j++)
            {
                if (prime[j] == 1)
                {
                    for (int k = max(j * j, (start + j - 1) / j * j); k <= end; k += j)
                    {
                        prime[k] = 0;
                    }
                }
            }
        }));
    }

    for (int i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    // print last 10 primes
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
    sort(list.begin(), list.end());

    list.insert(list.begin(), sum);
    list.insert(list.begin(), prime_count);
    list.insert(list.begin(), duration.count());
    
    for (int i = 0; i < list.size(); i++)
    {
        myfile << list[i];
        if (i == 0)
            myfile << "ms" << " ";
        else
            myfile << " ";
    }
    myfile << endl;
}

void single_thread_sieve(ofstream &myfile)
{
    auto start = std::chrono::high_resolution_clock::now();
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
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    // print last 10 primes
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
    list.insert(list.begin(), duration.count());
    for (int i = 0; i < list.size(); i++)
    {
        myfile << list[i];
        if (i == 0)
            myfile << "ms" << " ";
        else
            myfile << " ";
    }
}