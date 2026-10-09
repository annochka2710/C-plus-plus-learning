#ifndef WRITER_H
#define WRITER_H

#include "interfaces.h"
#include <iostream>

// Приемник
class Writer : public Consumer {
public:
    void show(int value, int channel) override {
        std::cout << "Writer: " << value << " - " << channel << std::endl;
    }
};

#endif
