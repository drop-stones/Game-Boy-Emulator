#include "CPU.hpp"

namespace gbe {
/************************/
/* class CPU            */
/************************/

// Execute instruction
void
CPU::execute(Instruction ins, ArithmeticTarget target)
{
    std::uint8_t value = fetch_value(target);
    switch(ins) {
    case ADD:   regs.a = add(value);
    default:    break;
    }
}

// Fetch the value from register
//  - Convert "ArithmeticTarget" into "std::uint8_t"
std::uint8_t
CPU::fetch_value(ArithmeticTarget target)
{
    switch(target) {
    case a:     return regs.a;
    case b:     return regs.b;
    case c:     return regs.c;
    case d:     return regs.d;
    case e:     return regs.e;
    case h:     return regs.h;
    case l:     return regs.l;
    default:    return   0x00;
    }
}

// ADD instruction
//  - Read the value from target register
//  - Add the value into 'a' register
//  - Update flags register
std::uint8_t
CPU::add(std::uint8_t value)
{
    std::uint16_t new_value = static_cast<std::uint16_t>(regs.a) + static_cast<std::uint16_t>(value);
    std::uint8_t upper = static_cast<std::uint8_t>(new_value >> 8);
    std::uint8_t new_a = static_cast<std::uint8_t>(new_value & 0x00FF);
    regs.set_flags({(new_a == 0), false, ((regs.a & 0x0F) + (value & 0x0F) > 0x0F), (upper > 0)});
    return new_a;
}
} // gbe