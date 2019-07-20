#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <fstream>

size_t const thread_count = 10;
volatile int current_thread_index = 0;
std::mutex m;
std::condition_variable cv;


int main() {
    /*
        Can i do it like that?
        
        std::ofstream fout("output.txt");

        #pragma omp parallel for num_threads(10) ordered
        for (int i = 0; i < 10; i++) {
            int num = i % 2 == 0 ? i + 1 : i - 1;

            #pragma omp ordered
            {
                for (int j = num * 10 + 1; j <= (num + 1) * 10; j++) {
                    fout << j << " ";
                }

                fout << std::endl;
            }
        }

        fout.close();
    */
    
    
    
    std::vector<std::thread> threads;
    std::ofstream fout("output.txt");

    for (int i = 1; i <= thread_count; i++) {
        threads.emplace_back(std::thread([i, &fout] {
            std::unique_lock<std::mutex> ul(m);
            int this_thread_index = (i % 2 == 0) ? i - 1 : i + 1;
            cv.wait(ul, [&this_thread_index]() -> bool { return current_thread_index == this_thread_index; });

            for (int j = (i - 1) * thread_count + 1; j <= i * thread_count; j++) {
                fout << j << " ";
            }

            fout << "\r\n";

            current_thread_index++;
            cv.notify_all();
        }));
    }

    current_thread_index = 1;
    cv.notify_all();

    for (auto &thread : threads) {
        thread.join();
    }

    threads.clear();
    fout.close();

    return 0;
}
