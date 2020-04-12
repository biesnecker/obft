#include "opts.h"

#include <iostream>

#include "fmt/core.h"

namespace obft {

OptsParsingException::OptsParsingException(const std::string& message)
    : message_(message) {}

const char* OptsParsingException::what() const throw() {
    return message_.c_str();
}

Opts::Opts() : filename_(), optimize_(false), verbose_(false) {}

void Opts::parseArgs(int argc, char** argv) {
    optimize_ = false;
    verbose_ = false;
    for (int i = 0; i < argc; ++i) {
        if (i + 1 == argc) {
            // The last argument is always the filename
            filename_ = std::string(argv[i]);
        } else if (argv[i] != nullptr && argv[i][0] == '-') {
            parseFlag(++argv[i]);
        } else {
            throw OptsParsingException(
                fmt::format("Unknown option: {}", argv[i]));
        }
    }
}

const std::string& Opts::filename() const { return filename_; }
bool Opts::interpret() const { return interpret_; }
bool Opts::optimize() const { return optimize_; }
bool Opts::verbose() const { return verbose_; }

void Opts::printOptions() const {
    std::cout << fmt::format(
        "Options:\n"
        "- FILENAME:\t{}\n"
        "- INTERPRET:\t{}\n"
        "- OPTIMIZE:\t{}\n"
        "- VERBOSE:\t{}\n",
        filename_, interpret_, optimize_, verbose_);
}

void Opts::parseFlag(const std::string& flags) {
    if (flags.empty()) {
        throw OptsParsingException("Unknown flag: -");
    }
    for (const auto c : flags) {
        switch (c) {
            case 'i':
                interpret_ = true;
                break;
            case 'o':
                optimize_ = true;
                break;
            case 'v':
                verbose_ = true;
                break;
            default:
                throw OptsParsingException(fmt::format("Unknown flag: {}", c));
        }
    }
}

}  // namespace obft