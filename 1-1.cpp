#include <iostream>
#include <chrono>
using namespace std::chrono;

template <class T>
class Timer{
private:
    steady_clock::time_point start;
    steady_clock::time_point start_pause;
    int delay=0;
    int check= 1;
public:
    Timer(): start(steady_clock::now()){}

    ~Timer(){
        if (check!=1){ delay += duration_cast<T>(steady_clock::now()-start_pause).count();}
        auto duration = duration_cast<T>(steady_clock::now()-start).count()-delay;
        std::cout << "It lasted: " << duration <<std::endl;
    }

    void Pause(){
        if (check==1) {
            start_pause = steady_clock::now();
            check = 0;
        } else{
            std::cout << "Can't Pause again"<<std::endl;
        }
    }

    void Unpause(){
        if (check != 1) {
            delay += duration_cast<T>(steady_clock::now() - start_pause).count();
            check = 1;
        } else{
            std::cout << "Can't unpause because it is not paused"<<std::endl;
        }
    }

};

int main() {
    auto result=0.;
    {
        Timer<milliseconds> t;
        int n=10000;
        for(auto i=0; i <n;i++) {
            for (auto j=0; j<n;j++){ result += i-j;}
        }
        t.Pause();
        t.Pause();
        for(auto i=0; i <n;i++) {
            for (auto j=0; j<n;j++){ result += i-j;}
        }
    }
    std::cout << "Result is  "<<result;
}
