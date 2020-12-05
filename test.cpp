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

    if (flags.zero == flags2.zero && flags.subtract == flags2.subtract
        && flags.half_carry == flags2.half_carry && flags.carry == flags2.carry)
            return true;
    
    return false;
}

bool test_CPU (void)
{
    class CPU cpu;
    cpu.regs.a = 0xff;
    cpu.regs.c = 0x01;
    Instruction ins = ADD;
    ArithmeticTarget target = c;
    cpu.execute(ins, target);
    struct FlagsRegister flags = cpu.regs.get_flags();

    //if (cpu.regs.a == 0x00 && cpu.regs.c == 0x01
    // && flags.zero == true && flags.subtract == false && flags.half_carry == true && flags.carry == true)
    //    return true;

    cpu.regs.a = 0x04;
    cpu.regs.c = 0x08;
    cpu.execute(ins, target);
    flags = cpu.regs.get_flags();

    if (cpu.regs.a == 0x0c && cpu.regs.c == 0x08
     && flags.zero == false && flags.subtract == false && flags.half_carry == false && flags.carry == false)
        return true;
    
    cerr << "regs.a: 0x" << hex << static_cast<uint>(cpu.regs.a) << '\n';
    cerr << "regs.c: 0x" << hex << static_cast<uint>(cpu.regs.c) << '\n';
    cerr << "flags.zero: " << flags.zero << '\n';
    cerr << "flags.subtract: " << flags.subtract << '\n';
    cerr << "flags.half_carry: " << flags.half_carry << '\n';
    cerr << "flags.carry: " << flags.carry << '\n';
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