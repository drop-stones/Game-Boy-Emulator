#include "register.hpp"
#include "CPU.hpp"

#include <string>
#include <iostream>     // cerr
#include <sstream>      // hex

using namespace std;
using namespace gbe;

bool test_registers (void)
{
    struct Registers regs;
    uint16_t af = 0x0123, bc = 0x4567, de = 0x89ab, hl = 0xcdef;

    // test a
    regs.a = 0xab;
    if (regs.a != 0xab)
        return false;
    // test c
    regs.c = 0xcd;
    if (regs.c != 0xcd)
        return false;

    // test af
    regs.set_af(af);
    if (af != regs.get_af())
        return false;
    // test bc
    regs.set_bc(bc);
    if (bc != regs.get_bc())
        return false;
    // test de
    regs.set_de(de);
    if (de != regs.get_de())
        return false;
    // test hl
    regs.set_hl(hl);
    if (hl != regs.get_hl())
        return false;

    // all test passes
    return true;
}

bool test_flags (void)
{
    struct FlagsRegister flags {0, 1, 1, 1};
    struct Registers regs;
    regs.set_flags(flags);
    struct FlagsRegister flags2 = regs.get_flags();
    struct FlagsRegister flags3;
    if (!(flags.zero == flags2.zero && flags.subtract == flags2.subtract
       && flags.half_carry == flags2.half_carry && flags.carry == flags2.carry))
        goto flags_error;

    flags.zero = 0; flags.subtract = 1; flags.half_carry = 0; flags.carry = 1;
    flags2.zero = 1; flags2.subtract = 0; flags.half_carry = 1; flags.carry = 0;
    flags3 = flags | flags2;
    if (!(flags3.zero && flags3.subtract && flags3.half_carry && flags3.carry))
        goto flags_error;

    // All test pass
    return true;

flags_error:
    return false;
}

bool test_CPU (void)
{
    class CPU cpu;
    struct FlagsRegister flags;
    Instruction ins;
    Operand operand;

    // ADD test 
    ins = Instruction::ADD;
    operand = Operand::c;
    cpu.regs.a = 0xff;
    cpu.regs.c = 0x01;
    cpu.execute(ins, operand);
    flags = cpu.regs.get_flags();
    if (!(cpu.regs.a == 0x00 && cpu.regs.c == 0x01
       && flags.zero == true && flags.subtract == false && flags.half_carry == true && flags.carry == true))
        goto error;

    cpu.regs.a = 0x04;
    cpu.regs.c = 0x08;
    cpu.execute(ins, operand);
    flags = cpu.regs.get_flags();
    if (!(cpu.regs.a == 0x0c && cpu.regs.c == 0x08
       && flags.zero == false && flags.subtract == false && flags.half_carry == false && flags.carry == false))
        goto error;

    // ADDHL
    ins = Instruction::ADDHL;
    operand = Operand::bc;
    cpu.regs.set_bc(0xff00);
    cpu.regs.set_hl(0x0100);
    cpu.execute(ins, operand);
    flags = cpu.regs.get_flags();
    if (!(cpu.regs.get_bc() == 0xff00 && cpu.regs.get_hl() == 0x0000
       && flags.zero == true && flags.subtract == false && flags.half_carry == true && flags.carry == true))
        goto error;

    // ADC
    ins = Instruction::ADC;
    operand = Operand::l;
    cpu.regs.a = 0xff;
    cpu.regs.l = 0x0f;
    cpu.regs.set_carry_flag(true);
    cpu.execute(ins, operand);
    flags = cpu.regs.get_flags();
    if (!(cpu.regs.a == 0x0f && cpu.regs.l == 0x0f
       && flags.zero == false && flags.subtract == false && flags.half_carry == true && flags.carry == true))
        goto error;

    cpu.regs.a = 0xff;
    cpu.regs.l = 0x01;
    cpu.regs.set_carry_flag(false);
    cpu.execute(ins, operand);
    flags = cpu.regs.get_flags();
    if (!(cpu.regs.a == 0x00 && cpu.regs.l == 0x01
       && flags.zero && !flags.subtract && flags.half_carry && flags.carry))
        goto error;

    // SUB
    ins = Instruction::SUB;
    operand = Operand::b;
    cpu.regs.a = 0xf0;
    cpu.regs.b = 0x0f;
    cpu.execute(ins, operand);
    flags = cpu.regs.get_flags();
    if (!(cpu.regs.a == 0x0e1 && cpu.regs.b == 0x0f
       && !flags.zero && flags.subtract && flags.half_carry && !flags.carry))
        goto error;

    // SBC
    ins = Instruction::SBC;
    operand = Operand::b;
    cpu.regs.a = 0x01;
    cpu.regs.b = 0x01;
    cpu.regs.set_carry_flag(true);
    cpu.execute(ins, operand);
    flags = cpu.regs.get_flags();
    if (!(cpu.regs.a == 0xff && cpu.regs.b == 0x01
          && !flags.zero && flags.subtract && flags.half_carry && flags.carry))
        goto error;

    // All test pass
    return true;

error:
    cpu.regs.print();
    return false;
}

void
print_result (std::string testName, bool testResult)
{
    cerr << testName << ": " << (testResult ? "Pass" : "Failed") << endl;
}

int main (int argc, char **argv)
{
    print_result("test_registers", test_registers());
    print_result("test_flags", test_flags());
    print_result("test_CPU", test_CPU());
}