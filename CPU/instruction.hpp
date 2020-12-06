#ifndef GB_EMULATOR_INSTRUCTION_HPP_
#define GB_EMULATOR_INSTRUCTION_HPP_

namespace gbe {

enum class Operand {
    a, b, c, d, e, h, l, bc, de, hl, sp, hli,
};

enum class Instruction {
    ADD,    /* add to 'a' register */
    ADDHL,  /* add to HL */
    ADC,    /* add with carry */
    SUB,    /* subtract */
    SBC,    /* subtract with carry */
    AND,    /* logical and */
    OR,     /* logical or */
    XOR,    /* logical xor */
    CP,     /* compare */
    INC,    /* increment */
    DEC,    /* decrement */
    CCF,    /* complement carry flag */
    SCF,    /* set carry flag */
    RRA,    /* rotate right 'a' register */
    RLA,    /* rotate left 'a' register */
    RRCA,   /* rotate right 'a' register */
    RRLA,   /* rotate left 'a' register */
    CPL,    /* complement 'a' register */
    BIT,    /* bit test */
    RESET,  /* bit reset */
    SET,    /* bit set */
    SRL,    /* shift right logical */
    RR,     /* rotate right */
    RL,     /* rotate left */
    RRC,    /* rotate right */
    RLC,    /* rotate left */
    SRA,    /* shift right arithmetic */
    SLA,    /* shift left arithmetic */
    SWAP,   /* swap nibbles */
};
} // gbe
#endif