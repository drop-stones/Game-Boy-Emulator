#include "CPU.hpp"

namespace gbe {
/************************/
/* class CPU            */
/************************/

// Execute instruction
void
CPU::execute(Instruction ins, Operand operand)
{
    //const std::uint8_t  &ref_to_reg = fetch_reg_ref(operand);
    const std::uint8_t  value_8bit  = fetch_8bit_value(operand);
    const std::uint16_t value_16bit = fetch_16bit_value(operand);
    switch(ins) {
    case Instruction::ADD:      ADD(value_8bit);    break;
    case Instruction::ADDHL:    ADDHL(value_16bit); break;
    case Instruction::ADC:      ADC(value_8bit);    break;
    case Instruction::SUB:      SUB(value_8bit);    break;
    case Instruction::SBC:      SBC(value_8bit);    break;
    case Instruction::AND:      AND(value_8bit);    break;
    case Instruction::OR:       OR (value_8bit);    break;
    case Instruction::XOR:      XOR(value_8bit);    break;
    case Instruction::CP:       CP (value_8bit);    break;
    case Instruction::INC:      INC(operand);       break;
    case Instruction::DEC:      DEC(operand);       break;
    case Instruction::CCF:
    case Instruction::SCF:
    case Instruction::RRA:
    case Instruction::RLA:
    case Instruction::RRCA:
    case Instruction::RRLA:
    case Instruction::CPL:
    case Instruction::BIT:
    case Instruction::RESET:
    case Instruction::SET:
    case Instruction::SRL:
    case Instruction::RR:
    case Instruction::RL:
    case Instruction::RRC:
    case Instruction::RLC:
    case Instruction::SRA:
    case Instruction::SLA:
    case Instruction::SWAP:
    default:    break;
    }
}

std::uint8_t *
CPU::fetch_reg_ptr(Operand operand)
{
    switch(operand) {
    case Operand::a:    return &regs.a;
    case Operand::b:    return &regs.b;
    case Operand::c:    return &regs.c;
    case Operand::d:    return &regs.d;
    case Operand::e:    return &regs.e;
    case Operand::h:    return &regs.h;
    case Operand::l:    return &regs.l;
    default:            return nullptr;
    }
}

// Fetch the value from register
//  - Convert "Operand" into "std::uint8_t"
const std::uint8_t
CPU::fetch_8bit_value(Operand operand) const
{
    switch(operand) {
    case Operand::a:    return regs.a;
    case Operand::b:    return regs.b;
    case Operand::c:    return regs.c;
    case Operand::d:    return regs.d;
    case Operand::e:    return regs.e;
    case Operand::h:    return regs.h;
    case Operand::l:    return regs.l;
    default:            return   0x00;
    }
}

// Fetch the value from register
//  - Convert "Operand" into "std::uint16_t"
const std::uint16_t
CPU::fetch_16bit_value(Operand operand) const
{
    switch(operand) {
    case Operand::bc:   return regs.get_bc();
    case Operand::de:   return regs.get_de();
    case Operand::hl:   return regs.get_hl();
    default:            return          0x00;
    }
}
} // gbe