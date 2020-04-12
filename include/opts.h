#pragma once

#include <exception>
#include <string>

namespace obft {

struct OptsParsingException : public std::exception {
    OptsParsingException(const std::string& message);
    virtual const char* what() const throw();

  private:
    std::string message_;
};

struct Opts {
    Opts();

    void parseArgs(int argc, char** argv);

    const std::string& filename() const;
    bool interpret() const;
    bool optimize() const;
    bool verbose() const;

    void printOptions() const;

  private:
    std::string filename_;
    bool interpret_;
    bool optimize_;
    bool verbose_;

    void parseFlag(const std::string& flags);
};

}  // namespace obft