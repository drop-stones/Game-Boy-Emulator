#include "CPU.hpp"

#include <limits>
#include <iostream>
#include <sstream>

namespace gbe {

// Check whether "val1 + val2 > Tmax"
template <typename T>
bool
is_overflow_add(T val1, T val2)
{
    //std::cerr << std::hex << (uint)val1 << " + " << (uint)val2 << " >? " << (uint)std::numeric_limits<T>::max();
    //std::cerr << " => " << (uint)(val1 > std::numeric_limits<T>::max() - val2) << std::endl;
    return val1 > std::numeric_limits<T>::max() - val2;
}

// Check whether "val1 - val2 < 0"
template <typename T>
bool
is_overflow_sub(T val1, T val2)
{
    return val1 < val2;
}

// Check half_overflow
//   8bit  => 4bit overflow  (half_max = 0b00001111)
//   16bit => 12bit overflow (half_max = 0b0000111111111111)
template <typename T>
bool
is_half_overflow_add(T val1, T val2)
{
    T half_max = std::numeric_limits<T>::max() >> 4;
    return (val1 & half_max) + (val2 & half_max) > half_max;
}

template <typename T>
bool
is_half_overflow_sub(T val1, T val2)
{
    T half_max = std::numeric_limits<T>::max() >> 4;
    //std::cerr << "half_max: "  << std::hex << (uint)half_max << std::endl;
    //std::cerr << std::hex << (uint)(val1 & half_max) << " < " << (uint)(val2 & half_max);
    //std::cerr << " => " << (uint)(val1 > std::numeric_limits<T>::max() - val2) << std::endl;
    return (val1 & half_max) < (val2 & half_max);
}

// ADD instruction
//  - Read the value from target register
//  - Add the value into 'a' register
//  - Update flags register
void
CPU::ADD(std::uint8_t value)
{
    const std::uint8_t new_a = regs.a + value;
    regs.set_flags({(new_a == 0), false, is_half_overflow_add<std::uint8_t>(regs.a, value), is_overflow_add<std::uint8_t>(regs.a, value)});
    regs.a = new_a;
}

// ADDHL
//  - Read 16bit value
//  - Add the value into 'hl' registers
//  - Update flags register
void
CPU::ADDHL(std::uint16_t value)
{
    const std::uint16_t new_hl = regs.get_hl() + value;
    regs.set_flags({(new_hl == 0), false, is_half_overflow_add<std::uint16_t>(regs.get_hl(), value), is_overflow_add<std::uint16_t>(regs.get_hl(), value)});
    regs.set_hl(new_hl);
}

// ADD with carry
void
CPU::ADC(std::uint8_t value)
{
    struct FlagsRegister flags1, flags2;
    ADD(static_cast<std::uint8_t>(regs.get_carry_flag()));
    flags1 = regs.get_flags();
    ADD(value);
    flags2 = regs.get_flags();
    regs.set_flags(flags1 + flags2);
}

// SUB from 'a' register
void
CPU::SUB(std::uint8_t value)
{
    const std::uint8_t new_a = regs.a - value;
    regs.set_flags({(new_a == 0), true, is_half_overflow_sub<std::uint8_t>(regs.a, value), is_overflow_sub<std::uint8_t>(regs.a, value)});
    regs.a = new_a;
}

void
CPU::SBC(std::uint8_t value)
{
    struct FlagsRegister flags1, flags2;
    SUB(static_cast<std::uint8_t>(regs.get_carry_flag()));
    flags1 = regs.get_flags();
    SUB(value);
    flags2 = regs.get_flags();
    regs.set_flags(flags1 + flags2);
}

void
CPU::AND(std::uint8_t value)
{
    regs.a = regs.a & value;
    regs.set_flags({(regs.a == 0), false, false, false});
    //regs.set_flags({(regs.a == 0), false, true, false});
}

void
CPU::OR(std::uint8_t value)
{
    regs.a = regs.a | value;
    regs.set_flags({(regs.a == 0), false, false, false});
}

void
CPU::XOR(std::uint8_t value)
{
    regs.a = regs.a ^ value;
    regs.set_flags({(regs.a == 0), false, false, false});
}

void
CPU::CP(std::uint8_t value)
{
    regs.set_flags({(regs.a == 0), true, is_half_overflow_sub<std::uint8_t>(regs.a, value), is_overflow_sub<std::uint8_t>(regs.a, value)});
}

} // gbe
