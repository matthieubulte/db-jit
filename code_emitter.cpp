#include "code_emitter.hpp"

#include "isa/instructions.hpp"

void code_emitter::write_byte(unsigned char b) {
  base[offset++] = (signed char)b;
}

void code_emitter::write_bytes(int argc, const unsigned char* bytes) {
  for (int i = 0; i < argc; i++) {
    write_byte(bytes[i]);
  }
}

void code_emitter::write_imm(uint16_t imm) {
  *((uint16_t*)(base.get() + offset)) = imm;
  offset += 2;
}

void code_emitter::write_imm(uint32_t imm) {
  *((uint32_t*)(base.get() + offset)) = imm;
  offset += 4;
}

void code_emitter::write_imm(uint64_t imm) {
  *((uint64_t*)(base.get() + offset)) = imm;
  offset += 8;
}

unsigned long code_emitter::length() { return offset; }

char* code_emitter::get() { return base.get(); }