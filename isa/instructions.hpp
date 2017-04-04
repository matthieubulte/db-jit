#ifndef DB_JIT_INSTRUCTIONS_HPP_H
#define DB_JIT_INSTRUCTIONS_HPP_H

#include <cstdint>
#include "../code_emitter.hpp"

enum REGISTERS_64_STANDARD {
  RAX = 0,
  RCX = 1,
  RDX = 2,
  RBX = 3,
  RSP = 4,
  RBP = 5,
  RSI = 6,
  RDI = 7
};

enum REGISTERS_64_ADDITIONAL {
  R8 = 0,
  R9 = 1,
  R10 = 2,
  R11 = 3,
  R12 = 4,
  R13 = 5,
  R14 = 6,
  R15 = 7
};

enum REGISTERS_32_STANDARD {
  EAX = 0,
  ECX = 1,
  EDX = 2,
  EBX = 3,
  ESP = 4,
  EBP = 5,
  ESI = 6,
  EDI = 7
};

void OP_SIZE_64_STANDARD(code_emitter *e);
void OP_SIZE_64_ADDITIONAL(code_emitter *e);

template<REGISTERS_64_STANDARD R>
void MOV(code_emitter *e, uint64_t imm) {
  OP_SIZE_64_STANDARD(e);
  e->write_byte(((unsigned char)'\xb8') + R);
  e->write_imm(imm);
}

template<REGISTERS_64_ADDITIONAL R>
void MOV(code_emitter *e, uint64_t imm) {
  OP_SIZE_64_ADDITIONAL(e);
  e->write_byte(((unsigned char)'\xb8') + R);
  e->write_imm(imm);
}

template<REGISTERS_32_STANDARD R1, REGISTERS_64_STANDARD R2>
void MOV_FROM_REGISTER_AS_MEMORY(code_emitter *e) {
  e->write_byte('\x8b');
  e->write_byte((unsigned char)(R1*8 + R2));
};

template<REGISTERS_64_STANDARD R1, REGISTERS_32_STANDARD R2>
void MOV_TO_REGISTER_AS_MEMORY(code_emitter *e) {
  e->write_byte('\x89');
  e->write_byte((unsigned char)(R1 + R2*8));
};

template<REGISTERS_32_STANDARD R1, REGISTERS_32_STANDARD R2>
void ADD(code_emitter *e) {
  e->write_byte('\x01');
  e->write_byte(((unsigned char)'\xc0') + (unsigned char)(R2*8 + R1));
};

void RET(code_emitter *e);

#endif //DB_JIT_INSTRUCTIONS_HPP_H
