#pragma once

#include "ir.h"
#include "opts.h"

namespace obft {

struct InterpreterException : public std::exception {
    InterpreterException(const std::string& message);
    virtual const char* what() const throw();

  private:
    std::string message_;
};

struct Interpreter {
    Interpreter(std::shared_ptr<Opts> opts);

    uint8_t run(ProgramListing program) const;

  private:
    std::shared_ptr<Opts> opts_;
};

}  // namespace obft