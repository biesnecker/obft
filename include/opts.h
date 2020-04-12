#pragma once

#include <string>

#include "errors.h"

namespace obft {

DEFINE_RUNTIME_ERROR_TYPE(OptsParsingException);

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