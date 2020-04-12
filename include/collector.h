#pragma once

#include <memory>
#include <stack>
#include <vector>

#include "errors.h"
#include "ir.h"

namespace obft {

DEFINE_RUNTIME_ERROR_TYPE(CollectorException);

struct Collector {
    Collector();
    explicit Collector(size_t initial_capacity);

    void append(Instr&& i);

    std::unique_ptr<std::vector<Instr>> getInstructions();

  private:
    std::unique_ptr<std::vector<Instr>> instructions_;
    std::stack<int> brackets_;
    size_t idx_;
};
}  // namespace obft