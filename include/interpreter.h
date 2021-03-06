#pragma once

#include "ir.h"
#include "opts.h"

namespace obft {

struct Interpreter {
    Interpreter(std::shared_ptr<Opts> opts);

    uint8_t run(std::unique_ptr<std::vector<Instr>> program) const;

  private:
    std::shared_ptr<Opts> opts_;
};

}  // namespace obft