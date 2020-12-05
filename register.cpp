#include "register.hpp"

namespace gbe {
/************************/
/* struct Registers     */
/************************/

// Get 16bit from two 8bit registers
uint16_t
Registers::get_af()
{
    return static_cast<std::uint16_t>(a << 8)
           | static_cast<std::uint16_t>(f);
}

uint16_t
Registers::get_bc()
{
    return static_cast<std::uint16_t>(b << 8)
           | static_cast<std::uint16_t>(c);
}

uint16_t
Registers::get_de()
{
    return static_cast<std::uint16_t>(d << 8)
           | static_cast<std::uint16_t>(e);
}

uint16_t
Registers::get_hl()
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
Registers::get_flags()
{
    const bool zero = static_cast<bool>(f >> 7);
    const bool subtract = static_cast<bool>((f & 0x40) >> 6);
    const bool half_carry = static_cast<bool>((f & 0x20) >> 5);
    const bool carry = static_cast<bool>((f & 0x10) >> 4);
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

/************************/
/* class FlagsRegister  */
/************************/

} // gbe