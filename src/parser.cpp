#include "parser.h"

#include <fstream>
#include <iostream>
#include <iterator>
#include <stack>

#include "fmt/core.h"

namespace obft {

Parser::Parser(std::shared_ptr<Opts> opts) : opts_(opts) {}

ProgramListing Parser::parse() const {
    std::ifstream source(opts_->filename(), std::fstream::in);
    if (!source) {
        throw ParserException(
            fmt::format("Could not open source file: {}", opts_->filename()));
    }

    auto ir = std::make_unique<std::vector<Instr>>();

    std::stack<int> brackets;

    int idx = 0;
    int last_open = 0;

    for (std::istreambuf_iterator<char> i(source), e; i != e; ++i) {
        char c = *i;
        switch (c) {
            case '<':
                ir->emplace_back(shift_left_instr(1));
                ++idx;
                break;
            case '>':
                ir->emplace_back(shift_right_instr(1));
                ++idx;
                break;
            case '+':
                ir->emplace_back(increment_instr(1));
                ++idx;
                break;
            case '-':
                ir->emplace_back(decrement_instr(1));
                ++idx;
                break;
            case ',':
                ir->emplace_back(read_instr());
                ++idx;
                break;
            case '.':
                ir->emplace_back(write_instr());
                ++idx;
                break;
            case '[':
                ir->emplace_back(open_instr());
                brackets.push(idx);
                ++idx;
                break;
            case ']':
                if (brackets.empty()) {
                    throw ParserException(fmt::format(
                        "Unmatched close bracket at index {}", idx));
                }

                // Get the last open index.
                last_open = brackets.top();
                // Set its target to the index after this one.
                ir->at(last_open).setArg0(idx + 1);
                // And set the close bracket's target to the last open.
                ir->emplace_back(close_instr(last_open));
                brackets.pop();
                ++idx;
                break;
            default:
                // Ignore unmatched characters.
                break;
        }
    }

    // Insert the EOF instruction.
    ir->emplace_back(eof_instr());

    // If there's still an unmatched open bracket that's a problem.
    if (!brackets.empty()) {
        throw ParserException(
            fmt::format("Unmatched open bracket at index {}", brackets.top()));
    }
    if (opts_->verbose()) {
        std::cout << "Raw instruction count: " << ir->size() << std::endl;
        for (const auto& i : *ir) {
            std::cout << i << "\n";
        }
    }
    return ir;
}

}  // namespace obft