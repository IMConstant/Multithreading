#include <iostream>
#include <Poco/Event.h>
#include <Poco/Runnable.h>
#include <Poco/RunnableAdapter.h>
#include <Poco/ThreadPool.h>
#include <functional>

#include "DataBase.h"

#define SEQUENCE_LENGTH 10

volatile int currentThreadIndex = 0;
DataBase dataBase("simple.db");


class SQLWriter : public Poco::Runnable {
    std::reference_wrapper<Poco::Event> event;
    int thisThreadIndex;
    int firstNumber;

public:
    explicit SQLWriter(int i, std::reference_wrapper<Poco::Event> _event) :
            thisThreadIndex((i % 2 == 0) ? i - 1 : i + 1),
            event(_event),
            firstNumber(i) {}

    void run() override {
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
        std::string str;

        for (int j = (firstNumber - 1) * SEQUENCE_LENGTH + 1; j <= firstNumber * SEQUENCE_LENGTH; j++) {
            str += std::to_string(j) + " ";
        }

        str.pop_back();
        dataBase.add(str);
    }
};

int main() {
    Poco::Event event(false);
    Poco::ThreadPool threadPool;

    for (int i = 1; i <= 10; i++) {
        auto *writer = new SQLWriter(i, event);
        threadPool.start(*writer);
    }

    currentThreadIndex = 1;
    event.set();
    threadPool.joinAll();

    //dataBase.read();

    return 0;
}