#include "interpreter.h"

#include <array>
#include <cstdio>
#include <vector>

namespace obft {

constexpr auto TAPE_LENGTH = 30000;

InterpreterException::InterpreterException(const std::string& message)
    : message_(message) {}

const char* InterpreterException::what() const throw() {
    return message_.c_str();
}

Interpreter::Interpreter(std::shared_ptr<Opts> opts) : opts_(opts) {}

uint8_t Interpreter::run(ProgramListing program) const {
    auto pc_start = program->data();
    auto pc = pc_start;
    std::array<uint8_t, TAPE_LENGTH> tape{};
    auto tape_ptr = tape.data();

    bool running = true;

    uint8_t rval = 0;

    while (running) {
        switch (pc->getOpcode()) {
            case Opcode::SHIFT_RIGHT:
                tape_ptr += (pc++)->getArg0();
                break;
            case Opcode::SHIFT_LEFT:
                tape_ptr -= (pc++)->getArg0();
                break;
            case Opcode::INCREMENT:
                *tape_ptr += (pc++)->getArg0();
                break;
            case Opcode::DECREMENT:
                *tape_ptr -= (pc++)->getArg0();
                break;
            case Opcode::READ:
                *tape_ptr = std::getchar();
                ++pc;
                break;
            case Opcode::WRITE:
                std::putchar(*tape_ptr);
                ++pc;
                break;
            case Opcode::OPEN:
                if (*tape_ptr == 0) {
                    pc = pc_start + pc->getArg0();
                } else {
                    ++pc;
                }
                break;
            case Opcode::CLOSE:
                if (*tape_ptr != 0) {
                    pc = pc_start + pc->getArg0();
                } else {
                    ++pc;
                }
                break;
            case Opcode::END_OF_FILE:
                rval = *tape_ptr;
                running = false;
                break;
        }
    }

    return rval;
}

}  // namespace obft