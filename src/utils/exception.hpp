/*
    Definições para manipulação de erros
*/

#pragma once

#include <exception>
#include <string>

class Exception : public std::exception {
    public:
        Exception(std::string msg, std::string details = "") throw();
        std::string message(void);

    private:
        std::string error_msg;
};
