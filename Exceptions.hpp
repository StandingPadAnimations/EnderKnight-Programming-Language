#ifndef EKException
#define EKException

#include <exception>
#include <iostream>
#include <string>

namespace error{
class LexerException: public std::exception {
    private:
        std::string message_;
    public:
        explicit LexerException(const std::string& message);
        const char* what() const noexcept override {
            return message_.c_str();
        }
};
inline LexerException::LexerException(const std::string& message) : message_(message) {
}

class ParserException: public std::exception {
    private:
        std::string message_;
    public:
        explicit ParserException(const std::string& message);
        const char* what() const noexcept override {
            return message_.c_str();
        }
};
inline ParserException::ParserException(const std::string& message) : message_(message) {
}

class EvalException: public std::exception {
    private:
        std::string message_;
    public:
        explicit EvalException(const std::string& message);
        const char* what() const noexcept override {
            return message_.c_str();
        }
};
inline EvalException::EvalException(const std::string& message) : message_(message) {
}
}

#endif