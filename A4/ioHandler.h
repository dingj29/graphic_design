//
// Created by WILL on 2021/12/6.
//
#include <vector>
#include "object.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#ifndef INC_3GC3_A4_IOHANDLER_H
#define INC_3GC3_A4_IOHANDLER_H


class ioHandler {
public:
    static void saveGame(std::vector<Object> objects);
    static std::vector<Object> loadGame();

private:
    ioHandler();
};


#endif //INC_3GC3_A4_IOHANDLER_H
