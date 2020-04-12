#include "parser.h"

#include <fstream>
#include <iostream>
#include <iterator>
#include <stack>

#include "collector.h"
#include "fmt/core.h"

namespace obft {

Parser::Parser(std::shared_ptr<Opts> opts) : opts_(opts) {}

std::unique_ptr<std::vector<Instr>> Parser::parse() const {
    std::ifstream source(opts_->filename(), std::fstream::in);
    if (!source) {
        throw ParserException(
            fmt::format("Could not open source file: {}", opts_->filename()));
    }

    Collector ir;

    for (std::istreambuf_iterator<char> i(source), e; i != e; ++i) {
        switch (*i) {
            case '<':
                ir.append(shift_left_instr(1));
                break;
            case '>':
                ir.append(shift_right_instr(1));
                break;
            case '+':
                ir.append(increment_instr(1));
                break;
            case '-':
                ir.append(decrement_instr(1));
                break;
            case ',':
                ir.append(read_instr());
                break;
            case '.':
                ir.append(write_instr());
                break;
            case '[':
                ir.append(open_instr());
                break;
            case ']':
                ir.append(close_instr(0));
                break;
            default:
                // Ignore unmatched characters.
                break;
        }
    }

    // Insert the EOF instruction.
    ir.append(eof_instr());
    auto instructions = ir.getInstructions();
    if (opts_->verbose()) {
        std::cout << "Raw instruction count: " << instructions->size()
                  << std::endl;
        for (const auto& i : *instructions) {
            std::cout << i << "\n";
        }
    }
    return instructions;
}

}  // namespace obft