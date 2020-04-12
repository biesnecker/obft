#include "ir.h"

namespace obft {

Instr::Instr(Opcode op) : Instr(op, 0, 0, 0) {}

Instr::Instr(Opcode op, int arg0) : Instr(op, arg0, 0, 0) {}

Instr::Instr(Opcode op, int arg0, int arg1) : Instr(op, arg0, arg1, 0) {}

Instr::Instr(Opcode op, int arg0, int arg1, int arg2)
    : op_(op), arg0_(arg0), arg1_(arg1), arg2_(arg2) {}

Opcode Instr::getOpcode() const { return op_; }
int Instr::getArg0() const { return arg0_; }
int Instr::getArg1() const { return arg1_; }
int Instr::getArg2() const { return arg2_; }
void Instr::setArg0(int v) { arg0_ = v; }
void Instr::setArg1(int v) { arg1_ = v; }
void Instr::setArg2(int v) { arg2_ = v; }

std::ostream& operator<<(std::ostream& os, const Instr& i) {
    switch (i.getOpcode()) {
        case Opcode::SHIFT_RIGHT:
            os << "SHIFT_RIGHT\t" << i.getArg0();
            break;
        case Opcode::SHIFT_LEFT:
            os << "SHIFT_LEFT\t" << i.getArg0();
            break;
        case Opcode::INCREMENT:
            os << "INCREMENT\t" << i.getArg0();
            break;
        case Opcode::DECREMENT:
            os << "DECREMENT\t" << i.getArg0();
            break;
        case Opcode::WRITE:
            os << "WRITE";
            break;
        case Opcode::READ:
            os << "READ";
            break;
        case Opcode::OPEN:
            os << "OPEN" << i.getArg0();
            break;
        case Opcode::CLOSE:
            os << "CLOSE" << i.getArg0();
            break;
        case Opcode::END_OF_FILE:
            os << "END_OF_FILE";
            break;
    }
    return os;
}

/* Helper functions */

Instr eof_instr() { return Instr(Opcode::END_OF_FILE); }
Instr shift_right_instr(int c) { return Instr(Opcode::SHIFT_RIGHT, c); }
Instr shift_left_instr(int c) { return Instr(Opcode::SHIFT_LEFT, c); }
Instr increment_instr(int c) { return Instr(Opcode::INCREMENT, c); }
Instr decrement_instr(int c) { return Instr(Opcode::DECREMENT, c); }
Instr write_instr() { return Instr(Opcode::WRITE); }
Instr read_instr() { return Instr(Opcode::READ); }
Instr open_instr() { return Instr(Opcode::OPEN); }
Instr close_instr(int c) { return Instr(Opcode::CLOSE, c); }

}  // namespace obft