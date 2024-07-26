/*
    Definições para manipulação de erros
*/

#include "exception.hpp"

Exception::Exception(std::string msg, std::string details) throw() : std::exception() {
    this->error_msg = msg;

    if (details != "") {
        error_msg += "Details: " + details;
    }
}

std::string Exception::message(void) {
    return this->error_msg;
}
