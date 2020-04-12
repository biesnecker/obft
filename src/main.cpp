#include <iostream>
#include <memory>

#include "consts.h"
#include "fmt/core.h"
#include "interpreter.h"
#include "opts.h"
#include "parser.h"

void printUsage() {
    std::cout << "USAGE: obft [-ov] FILENAME\n\n"
              << " -o\tenable optimizations\n"
              << " -v\tverbose\n";
}

void printHeader() {
    std::cout << fmt::format("{} {}\n", BINARY_NAME, VERSION)
              << "An optimizing brainfuck compiler.\n\n";
    printUsage();
}

int main(int argc, char** argv) {
    if (argc == 1) {
        printHeader();
        return EXIT_FAILURE;
    }
    try {
        auto opts = std::make_shared<obft::Opts>();
        opts->parseArgs(argc - 1, ++argv);
        if (opts->verbose()) {
            opts->printOptions();
        }
        obft::Parser parser{opts};
        auto prog = parser.parse();
        if (opts->interpret()) {
            obft::Interpreter interpreter{opts};
            auto res = interpreter.run(std::move(prog));
            std::cout << "Program result: " << unsigned(res) << std::endl;
        }
    } catch (const obft::OptsParsingException& e) {
        std::cout << e.what() << "\n\n";
        printUsage();
        return EXIT_FAILURE;
    } catch (const std::exception& e) {
        std::cout << e.what() << "\n\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
