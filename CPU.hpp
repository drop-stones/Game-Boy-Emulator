#ifndef GB_EMULATOR_CPU_HPP_
#define GB_EMULATOR_CPU_HPP_

#include "register.hpp"

namespace gbe {
enum ArithmeticTarget {
    a, b, c, d, e, h, l,
};

enum Instruction {
    ADD,
};

class CPU {
public:
    struct Registers regs;

    CPU() : regs() {}
    void execute(Instruction ins, ArithmeticTarget target);

private:
    std::uint8_t fetch_value(ArithmeticTarget target);
    std::uint8_t add(std::uint8_t value);
};
} // gbe
#endif