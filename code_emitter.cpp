#include "code_emitter.hpp"

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

VOID_FUNCTION code_emitter::compile() {
  void *mem = mmap(NULL, length(), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
  functions.push_back(std::make_pair(mem, offset));
  memcpy(mem, get(), length());
  mprotect(mem, length(), PROT_READ | PROT_EXEC);
  return (VOID_FUNCTION)mem;
}
