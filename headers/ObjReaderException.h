//
// Created by Ренат Асланов on 25.10.2024.
//

#ifndef OBJREADEREXCEPTION_H
#define OBJREADEREXCEPTION_H

#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>

class ObjReaderException : public std::runtime_error {
public:
    ObjReaderException(const std::string& message, int lineInd)
        : std::runtime_error(message + " at line " + std::to_string(lineInd)) {}
};


#endif //OBJREADEREXCEPTION_H
