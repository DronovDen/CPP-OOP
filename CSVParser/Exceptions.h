#pragma once
#include <exception>

class my_exception : public std::exception
{

public:
    my_exception(std::string const &message) : msg(message) {}
    char const *what() const noexcept override
    {
        return msg.c_str();
    }

private:
    std::string msg{};
};
