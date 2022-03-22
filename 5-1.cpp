#include <iostream>
#include <numeric>
#include <vector>
#include <thread>
#include <chrono>
using namespace std::chrono;
// 1. Проверить размер. Если он мал, то не распараллеливаем.
// 2. Определить количество исполнителей -- спросить у ОС.
// 3. Распределить данные между исполнителями.
// 4. Запустить исполнение.
// 5. Собрать ответы.

template <class T>
class Timer {
private:
    steady_clock::time_point start;
public:
    Timer() : start(steady_clock::now()) {}

    ~Timer() {
        auto duration = duration_cast<T>(steady_clock::now() - start).count();
        std::cout << duration << "  microseconds"<< std::endl;
    }
};

template <typename Iterator, typename T>
void accumulate_wrapper(Iterator begin, Iterator end, T init, T& result) {
    result = std::accumulate(begin, end, init);
}

template <typename Iterator, typename T>
T parallel_accumulate(Iterator begin, Iterator end, T init, int N) {
    // Размер диапазона
    auto size = std::distance(begin, end);
    // Количество исполнителей
    auto num_workers = N;
    if (num_workers>std::thread::hardware_concurrency()){
        std::cout<< "You goofed up, man!"<<std::endl;
        return 0;
    }
    // Проверяем, нужно ли распараллеливать
    // Распараллеливать всё-таки нужно, тогда:
    // Считаем количество данных на одного исполнителя
    if (size < num_workers * 4) {
        return std::accumulate(begin, end, init);
    }
    auto size_per_worker = size / num_workers;
    // Создаём два вектора: с потоками и для записи результатов
    std::vector<std::thread> threads;
    std::vector<T> results(num_workers - 1);
    // Распределяем данные и запускаем потоки.
    for(auto i = 0u; i < num_workers - 1; i++) {
        threads.push_back(std::thread(accumulate_wrapper<Iterator, T>,
                                      std::next(begin, i * size_per_worker), // сдвиг begin
                                      std::next(begin, (i + 1) * size_per_worker), // сдвиг begin
                                      0, // init
                                      std::ref(results[i]))); // для записи результата
    }
    // Производим расчёт и в основном потоке (с учётом переданного init)
    auto main_result = std::accumulate(
            std::next(begin, (num_workers - 1) * size_per_worker),
            end, init);

    // Ждём, пока остальные потоки завершат работу
    for(auto& thread: threads) {
        thread.join();
    }
    // Собираем все вычисленные результаты
    return std::accumulate(std::begin(results),
                           std::end(results), main_result);
}

int main() {
    std::vector<int> sequence(3000);
    std::iota(std::begin(sequence), std::end(sequence), 0);
    for(int N=1;N<10;N++) {
        {
            std::cout<<"N="<<N<<"   ";
            Timer<microseconds> t;
            std::cout << parallel_accumulate(std::begin(sequence),
                                             std::end(sequence),
                                             0, N) <<"   ";
        }
    }
}