#ifndef CUBEEXCEPTION_H
#define CUBEEXCEPTION_H

#include <exception>
#include <string>

class CubeException : public std::exception
{
private:
    std::string msg;
    CubeException();
public:
    CubeException(const char* const what) {  this->msg = what; }
    CubeException(const std::string& what) { this->msg = what; }
    virtual const char* what() const throw() { return this->msg.c_str(); }      //Gets the exception message
    virtual ~CubeException() throw() {}
};

#endif // CUBEEXCEPTIONS_H
