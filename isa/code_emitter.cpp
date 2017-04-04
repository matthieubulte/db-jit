#include "code_emitter.hpp"

void code_emitter::write_byte(unsigned char b) {
  char c = (signed char)b;
  base.push_back(c);
}

void code_emitter::write_bytes(int argc, const unsigned char* bytes) {
  for (int i = 0; i < argc; i++) {
    write_byte(bytes[i]);
  }
}

void code_emitter::write_imm(uint16_t imm) {
  write_bytes(2, reinterpret_cast<const unsigned char*>(&imm));
}

void code_emitter::write_imm(uint32_t imm) {
  write_bytes(4, reinterpret_cast<const unsigned char*>(&imm));
}

void code_emitter::write_imm(uint64_t imm) {
  write_bytes(8, reinterpret_cast<const unsigned char*>(&imm));
}

void code_emitter::add(REGISTERS::STANDARD_32 TO, REGISTERS::STANDARD_32 FROM) {
  write_byte('\x01');
  write_byte(((unsigned char)'\xc0') + (unsigned char)(FROM*8 + TO));
}

void code_emitter::move(REGISTERS::STANDARD_64 TO, uint64_t imm) {
  OP_SIZE_64_STANDARD();
  write_byte(((unsigned char)'\xb8') + TO);
  write_imm(imm);
}

void code_emitter::move(REGISTERS::STANDARD_32 TO, REGISTERS::MEMORY_ACCESS&& FROM) {
  switch(FROM.type) {
    case REGISTERS::REGISTER_TYPE::standard_64: {
      write_byte('\x8b');
      write_byte((unsigned char)(TO*8 + FROM.reg));
    } break;
    default: {
      throw new std::runtime_error("Not implemented yet.");
    }
  }
}
void code_emitter::move(REGISTERS::MEMORY_ACCESS&& TO, REGISTERS::STANDARD_32 FROM) {
  switch(TO.type) {
    case REGISTERS::REGISTER_TYPE::standard_64: {
      write_byte('\x89');
      write_byte((TO.reg + FROM*8));
    } break;
    default: {
      throw new std::runtime_error("Not implemented yet.");
    }
  }
}

void code_emitter::ret() {
  write_byte('\xc3');
}

void code_emitter::OP_SIZE_64_STANDARD() {
  write_byte('\x48');
}

void code_emitter::OP_SIZE_64_ADDITIONAL() {
  write_byte('\x49');
}

VOID_FUNCTION code_emitter::compile() {
  void *mem = mmap(NULL, base.size(), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
  functions.push_back(std::make_pair(mem, base.size()));
  memcpy(mem, base.data(), base.size());
  mprotect(mem, base.size(), PROT_READ | PROT_EXEC);
  return (VOID_FUNCTION)mem;
}
