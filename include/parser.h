#pragma once

#include <memory>
#include <vector>

#include "ir.h"
#include "opts.h"

namespace obft {

struct ParserException : public std::exception {
    ParserException(const std::string& message);
    virtual const char* what() const throw();

  private:
    std::string message_;
};

struct Parser {
    Parser(std::shared_ptr<Opts> opts);
    ProgramListing parse() const;

  private:
    std::shared_ptr<Opts> opts_;
};

}  // namespace obft