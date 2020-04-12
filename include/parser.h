#pragma once

#include <memory>
#include <vector>

#include "errors.h"
#include "ir.h"
#include "opts.h"

namespace obft {

DEFINE_RUNTIME_ERROR_TYPE(ParserException);

struct Parser {
    Parser(std::shared_ptr<Opts> opts);
    ProgramListing parse() const;

  private:
    std::shared_ptr<Opts> opts_;
};

}  // namespace obft