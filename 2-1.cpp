#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <array>
#include <chrono>
#include <algorithm>
using namespace std::chrono;

template <class T>
class Timer {
private:
    steady_clock::time_point start;
public:
    Timer() : start(steady_clock::now()) {}

    ~Timer() {
        auto duration = duration_cast<T>(steady_clock::now() - start).count();
        std::cout << duration << std::endl;
    }
};

int main() {
    std::array<int, 100> a1;
    std::vector<int> a2;
    std::deque<int> a3;
    std::list<int> a4;
    std::forward_list<int> a5;
    for (unsigned i=0;i<100;i++){
        int k=10-i;
        a1[i]=k;
        a2.push_back(k);
        a3.push_back(k);
        a4.push_back(k);
        a5.push_front(k);
    }
    std::cout << "Time spent sorting array:  ";
    {
        Timer<microseconds> t;
        std::sort(a1.begin(),a1.end());
    }
    std::cout << "Time spent sorting vector:  ";
    {
        Timer<microseconds> t;
        std::sort(a2.begin(),a2.end());
    }
    std::cout << "Time spent sorting deque:  ";
    {
        Timer<microseconds> t;
        std::sort(a3.begin(),a3.end());
    }
    std::cout << "Time spent sorting list:  ";
    {
        Timer<microseconds> t;
        a4.sort();
    }
    std::cout << "Time spent sorting forward_list:  ";
    {
        Timer<microseconds> t;
        a5.sort();
    }
    return 0;
}
