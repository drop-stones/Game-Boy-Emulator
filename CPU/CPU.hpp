#ifndef GB_EMULATOR_CPU_HPP_
#define GB_EMULATOR_CPU_HPP_

#include "register.hpp"
#include "instruction.hpp"

namespace gbe {
class CPU {
public:
    struct Registers regs;

    CPU() : regs() {}
    void execute(Instruction ins, Operand operand);

private:
    std::uint8_t* fetch_reg_ptr    (Operand operand);
    const std::uint8_t  fetch_8bit_value (Operand operand) const;
    const std::uint16_t fetch_16bit_value(Operand operand) const;
    void ADD    (std::uint8_t value);
    void ADDHL  (std::uint16_t value);
    void ADC    (std::uint8_t value);
    void SUB    (std::uint8_t value);
    void SBC    (std::uint8_t value);
    void AND    (std::uint8_t value);
    void OR     (std::uint8_t value);
    void XOR    (std::uint8_t value);
    void CP     (std::uint8_t value);
    void INC    (Operand operand);
    void DEC    (Operand operand);
};
} // gbe
#endif