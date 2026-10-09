#ifndef READER_H
#define READER_H

#include "interfaces.h"
#include <iostream>

// Источник или отправитель
class Reader : public Producer {
public:
    // читаем одно число
    bool exec() {
        int value;
        if(std::cin >> value) {
            // четные в канал 0, нечетные - в 1
            Producer::notify(value, value % 2);
            return true;
        }
        return false;
    }
};

#endif
