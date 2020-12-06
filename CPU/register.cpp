#include "register.hpp"

#include <iostream>
#include <sstream>

namespace gbe {
/************************/
/* struct Registers     */
/************************/

// Get 16bit from two 8bit registers
uint16_t
Registers::get_af() const
{
    return static_cast<std::uint16_t>(a << 8)
           | static_cast<std::uint16_t>(f);
}

uint16_t
Registers::get_bc() const
{
    return static_cast<std::uint16_t>(b << 8)
           | static_cast<std::uint16_t>(c);
}

uint16_t
Registers::get_de() const
{
    return static_cast<std::uint16_t>(d << 8)
           | static_cast<std::uint16_t>(e);
}

uint16_t
Registers::get_hl() const
{
    return static_cast<std::uint16_t>(h << 8)
           | static_cast<std::uint16_t>(l);
}

// Set 16bit into two 8bit registers
void
Registers::set_af(std::uint16_t af_val)
{
    a = static_cast<std::uint8_t>(af_val >> 8);      // Upper 8bit
    f = static_cast<std::uint8_t>(af_val & 0x00FF);  // Lower 8bit
}

void
Registers::set_bc(std::uint16_t bc_val)
{
    b = static_cast<std::uint8_t>(bc_val >> 8);      // Upper 8bit
    c = static_cast<std::uint8_t>(bc_val & 0x00FF);  // Lower 8bit
}

void
Registers::set_de(std::uint16_t de_val)
{
    d = static_cast<std::uint8_t>(de_val >> 8);      // Upper 8bit
    e = static_cast<std::uint8_t>(de_val & 0x00FF);  // Lower 8bit
}

void
Registers::set_hl(std::uint16_t hl_val)
{
    h = static_cast<std::uint8_t>(hl_val >> 8);      // Upper 8bit
    l = static_cast<std::uint8_t>(hl_val & 0x00FF);  // Lower 8bit
}

// Get flags from 'f' register 
struct FlagsRegister
Registers::get_flags() const
{
    const bool zero       = static_cast<bool>((f & 0b10000000) >> 7);
    const bool subtract   = static_cast<bool>((f & 0b01000000) >> 6);
    const bool half_carry = static_cast<bool>((f & 0b00100000) >> 5);
    const bool carry      = static_cast<bool>((f & 0b00010000) >> 4);
    struct FlagsRegister flags {zero, subtract, half_carry, carry};
    return flags;
}

// Set flags into upper 4bit of 'f' register
void
Registers::set_flags(struct FlagsRegister flags)
{
    f =   (flags.zero << 7) | (flags.subtract << 6)
        | (flags.half_carry << 5) | (flags.carry << 4)
        | (f & 0x0F);
}

// Get zero flag from 'f' register
bool
Registers::get_zero_flag() const
{
    return static_cast<bool>(f >> 7);
}

// Get subtract flag from 'f' register
bool
Registers::get_subtract_flag() const
{
    return static_cast<bool>((f & 0b01000000) >> 6);
}

// Get half_carry flag from 'f' register
bool
Registers::get_half_carry_flag() const
{
    return static_cast<bool>((f & 0b00100000) >> 5);
}

// Get carry flag from 'f' register
bool
Registers::get_carry_flag() const
{
    return static_cast<bool>((f & 0b00010000) >> 4);
}

// Set zero flag into 'f' register
void
Registers::set_zero_flag(const bool flag)
{
    if (flag) {
        f = f | 0b10000000;
    } else {
        f = f & 0b01111111;
    }
}

// Set subtract flag into 'f' register
void
Registers::set_subtract_flag(const bool flag)
{
    if (flag) {
        f = f | 0b01000000;
    } else {
        f = f & 0b10111111;
    }
}

// Set half_carry flag into 'f' register
void
Registers::set_half_carry_flag(const bool flag)
{
    if (flag) {
        f = f | 0b00100000;
    } else {
        f = f & 0b11011111;
    }
}

// Set carry flag into 'f' register
void
Registers::set_carry_flag(const bool flag)
{
    if (flag) {
        f = f | 0b00010000;
    } else {
        f = f & 0b11101111;
    }
}

// Utilities
void
Registers::print() const
{
    std::cerr << "a:\t\t0x"  << std::hex << static_cast<uint>(a) << '\n';
    std::cerr << "b:\t\t0x"  << std::hex << static_cast<uint>(b) << '\n';
    std::cerr << "c:\t\t0x"  << std::hex << static_cast<uint>(c) << '\n';
    std::cerr << "d:\t\t0x"  << std::hex << static_cast<uint>(d) << '\n';
    std::cerr << "e:\t\t0x"  << std::hex << static_cast<uint>(e) << '\n';
    std::cerr << "f:\t\t0x"  << std::hex << static_cast<uint>(f) << '\n';
    std::cerr << "h:\t\t0x"  << std::hex << static_cast<uint>(h) << '\n';
    std::cerr << "l:\t\t0x"  << std::hex << static_cast<uint>(l) << '\n';
    std::cerr << "af:\t\t0x" << std::hex << static_cast<uint>(get_af()) << '\n';
    std::cerr << "bc:\t\t0x" << std::hex << static_cast<uint>(get_bc()) << '\n';
    std::cerr << "de:\t\t0x" << std::hex << static_cast<uint>(get_de()) << '\n';
    std::cerr << "hl:\t\t0x" << std::hex << static_cast<uint>(get_hl()) << '\n';
    std::cerr << "zero:\t\t"       << get_zero_flag()       << '\n';
    std::cerr << "subtract:\t"   << get_subtract_flag()   << '\n';
    std::cerr << "half_carry:\t" << get_half_carry_flag() << '\n';
    std::cerr << "carry:\t\t"      << get_carry_flag()      << '\n';
}

/************************/
/* class FlagsRegister  */
/************************/

const struct FlagsRegister
FlagsRegister::operator| (const struct FlagsRegister &flags)
{
    zero       |= flags.zero;
    subtract   |= flags.subtract;
    half_carry |= flags.half_carry;
    carry      |= flags.carry;
    return *this;
}

const struct FlagsRegister
FlagsRegister::operator+ (const struct FlagsRegister &flags)
{
    zero        = flags.zero;           // final flags is ans
    subtract   |= flags.subtract;
    half_carry |= flags.half_carry;
    carry      |= flags.carry;
    return *this;
}

} // gbe