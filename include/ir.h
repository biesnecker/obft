#pragma once

#include <ostream>

namespace obft {

enum class Opcode {
    END_OF_FILE,
    SHIFT_RIGHT,
    SHIFT_LEFT,
    INCREMENT,
    DECREMENT,
    WRITE,
    READ,
    OPEN,
    CLOSE,
};

struct Instr {
    Instr(Opcode op);
    Instr(Opcode op, int arg0);
    Instr(Opcode op, int arg0, int arg1);
    Instr(Opcode op, int arg0, int arg1, int arg2);

    Opcode getOpcode() const;
    int getArg0() const;
    int getArg1() const;
    int getArg2() const;

    void setArg0(int v);
    void setArg1(int v);
    void setArg2(int v);

    friend std::ostream& operator<<(std::ostream& os, const Instr& i);

  private:
    Opcode op_;
    int arg0_;
    int arg1_;
    int arg2_;
};

Instr eof_instr();
Instr shift_right_instr(int c);
Instr shift_left_instr(int c);
Instr increment_instr(int c);
Instr decrement_instr(int c);
Instr write_instr();
Instr read_instr();
Instr open_instr();
Instr close_instr(int c);

using ProgramListing = std::unique_ptr<std::vector<Instr>>;

}  // namespace obft