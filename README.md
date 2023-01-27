# Parallel Sieve
##Methodology
since the goal was to split work among cores equally, I noticed that I can do 10^8 / 8 to split up the work equally.
Each thread got to run sieve on segments of 12500000. 
There are 2 lines in primes.txt and the first one is the concurrent version of sieve and 2nd one is sieve as one thread.

sometimes the compiler doesn't like how this is multi threaded so heres the commands
`g++ -o AS1 AS1.cpp -lpthread`
`./AS1`
