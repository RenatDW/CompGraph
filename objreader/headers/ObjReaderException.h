#ifndef OBJREADEREXCEPTION_H
#define OBJREADEREXCEPTION_H

#include <stdexcept>
#include <string>

class ObjReaderException : public std::runtime_error
{
public:
    ObjReaderException(const std::string &message, int lineInd)
        : std::runtime_error(message + " at line " + std::to_string(lineInd)) {}
};


#endif //OBJREADEREXCEPTION_H
