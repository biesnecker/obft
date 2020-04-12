#include "collector.h"

#include "fmt/core.h"

namespace obft {

Collector::Collector(size_t capacity)
    : instructions_(std::make_unique<std::vector<Instr>>(capacity)),
      brackets_(),
      idx_(0) {}

Collector::Collector() : Collector(0) {}

void Collector::append(Instr&& i) {
    auto op = i.getOpcode();
    size_t last_open = 0;
    switch (op) {
        case Opcode::NOP:
            return;
        case Opcode::OPEN:
            instructions_->emplace_back(std::move(i));
            brackets_.push(idx_);
            break;
        case Opcode::CLOSE:
            if (brackets_.empty()) {
                throw CollectorException(
                    fmt::format("Unmatched close bracket at index {}", idx_));
            }

            // Get the last open index.
            last_open = brackets_.top();
            // Set its target to the index after this one.
            instructions_->at(last_open).setArg0(idx_ + 1);
            // And set the close bracket's target to the last open.
            instructions_->emplace_back(close_instr(last_open));
            brackets_.pop();
            break;
        default:
            instructions_->emplace_back(std::move(i));
            break;
    }
    ++idx_;
}

std::unique_ptr<std::vector<Instr>> Collector::getInstructions() {
    if (!brackets_.empty()) {
        throw CollectorException(
            fmt::format("Unamtched open bracket at index {}", brackets_.top()));
    }
    return std::move(instructions_);
}

}  // namespace obft