#include <iostream>
#include <limits>
#include <chrono>
#include <thread>
#include <vector>

long long factorial(int n) 
{
    if (n <= 1) return 1;
    
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }

    return result;
}
    
void factorial_intensive_task() 
{
    int x = 0;

    int num = std::numeric_limits<int>::max();
    for(int i = 0; i < num; ++i) 
    {
       //std::cout << factorial(x) << "\n";
        factorial(x);   
        x = (x + 1) % 15;
    }
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    unsigned int num_threads = std::thread::hardware_concurrency();
    std::cout << "Number of threads: " << num_threads << "\n";
    std::vector<std::thread> threads;
    
    for (unsigned int i = 0; i < num_threads; ++i) {
        threads.emplace_back(factorial_intensive_task);
    }

    for (auto &thread : threads) {
        thread.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    
    std::cout << "Time taken by function: "
              << duration.count() << " seconds" << "\n";
}
