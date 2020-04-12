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
        auto instr = Instr::fromChar(*i);
        if (instr.has_value()) {
            ir.append(std::move(*instr));
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