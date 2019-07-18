#include <iostream>
#include <Poco/Event.h>
#include <Poco/Runnable.h>
#include <Poco/RunnableAdapter.h>
#include <Poco/ThreadPool.h>
#include <functional>

#define SEQUENCE_LENGTH 10

volatile int currentThreadIndex = 0;


class SQLWritter : public Poco::Runnable {
    std::reference_wrapper<Poco::Event> event;
    int thisThreadIndex;
    int firstNumber;

public:
    explicit SQLWritter(int i, std::reference_wrapper<Poco::Event> _event) :
            thisThreadIndex((i % 2 == 0) ? i - 1 : i + 1),
            event(_event),
            firstNumber(i) {}

    void run() {
        eventWait();
        SQLInsert();

        currentThreadIndex++;
        event.get().set();
    }

    void eventWait() {
        while (true) {
            event.get().wait();

            if (thisThreadIndex == currentThreadIndex) {
                event.get().reset();
                break;
            }
        }
    }

    void SQLInsert() {
        for (int j = (firstNumber - 1) * SEQUENCE_LENGTH + 1; j <= firstNumber * SEQUENCE_LENGTH; j++) {
            std::cout << j << " ";
        }

        std::cout << std::endl;
    }
};

int main() {
    Poco::Event event(false);
    Poco::ThreadPool threadPool;

    for (int i = 1; i <= 10; i++) {
        auto *writter = new SQLWritter(i, event);
        threadPool.start(*writter);
    }

    currentThreadIndex = 1;
    event.set();
    threadPool.joinAll();

    return 0;
}