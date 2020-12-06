#ifndef GB_EMULATOR_REGISTER_HPP_
#define GB_EMULATOR_REGISTER_HPP_

#include <cstdint>      // uintN_t

namespace gbe {
struct Registers {
    // 8bit registers
    std::uint8_t a;
    std::uint8_t b;
    std::uint8_t c;
    std::uint8_t d;
    std::uint8_t e;
    std::uint8_t f;     // flag register
    std::uint8_t h;
    std::uint8_t l;

    // 16bit getter
    std::uint16_t get_af() const;
    std::uint16_t get_bc() const;
    std::uint16_t get_de() const;
    std::uint16_t get_hl() const;

    // 16bit setter
    void set_af(std::uint16_t af_val);
    void set_bc(std::uint16_t bc_val);
    void set_de(std::uint16_t de_val);
    void set_hl(std::uint16_t hl_val);

    // Flags function
    struct FlagsRegister get_flags() const;
    void set_flags(struct FlagsRegister flags);
    bool get_zero_flag      () const;
    bool get_subtract_flag  () const;
    bool get_half_carry_flag() const;
    bool get_carry_flag     () const;
    void set_zero_flag      (const bool flag);
    void set_subtract_flag  (const bool flag);
    void set_half_carry_flag(const bool flag);
    void set_carry_flag     (const bool flag);

    // Utilities
    void print() const;

    Registers():
        a{0}, b{0}, c{0}, d{0}, e{0}, f{0}, h{0}, l{0} {}
};

// Upper 4bit of Registers::f
struct FlagsRegister {
    bool zero;
    bool subtract;
    bool half_carry;
    bool carry;

    FlagsRegister() : 
        zero {0}, subtract {0}, half_carry {0}, carry {0} {}
    FlagsRegister(bool z, bool s, bool h, bool c) :
        zero {z}, subtract {s}, half_carry {h}, carry {c} {}
    
    const struct FlagsRegister operator| (const struct FlagsRegister &flags);
    const struct FlagsRegister operator+ (const struct FlagsRegister &flags);
};
}// gbe

#endif