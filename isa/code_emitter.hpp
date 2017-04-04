#ifndef DB_JIT_CODE_EMITTER_H
#define DB_JIT_CODE_EMITTER_H

#include <cstdint>
#include <memory>
#include <unistd.h>
#include <sys/mman.h>
#include <cstring>
#include <cstdarg>
#include <vector>

typedef void (*VOID_FUNCTION)(void);

namespace REGISTERS {
  class STANDARD_64 {
  public:
    static enum R {
      RAX = 0,
      RCX = 1,
      RDX = 2,
      RBX = 3,
      RSP = 4,
      RBP = 5,
      RSI = 6,
      RDI = 7
    };
  };

  class ADDITIONAL_64 {
  public:
    static enum R {
      R8 = 0,
      R9 = 1,
      R10 = 2,
      R11 = 3,
      R12 = 4,
      R13 = 5,
      R14 = 6,
      R15 = 7
    };
  };

  class STANDARD_32 {
  public:
    static enum R {
      EAX = 0,
      ECX = 1,
      EDX = 2,
      EBX = 3,
      ESP = 4,
      EBP = 5,
      ESI = 6,
      EDI = 7
    };
  };
}

class code_emitter {
public:
  ~code_emitter() {
    for(auto &f : functions) {
      munmap(f.first, f.second);
    }
  }

  void write_byte(unsigned char b);
  void write_bytes(int argc, const unsigned char* bytes);
  void write_imm(uint16_t imm);
  void write_imm(uint32_t imm);
  void write_imm(uint64_t imm);

  void add(REGISTERS::STANDARD_32::R TO, REGISTERS::STANDARD_32::R FROM);
  void move(REGISTERS::STANDARD_64::R TO, uint64_t imm);

  void move_from_register_as_memory(REGISTERS::STANDARD_32::R R_TO, REGISTERS::STANDARD_64::R R_FROM);

  void move_to_register_as_memory(REGISTERS::STANDARD_64::R R_TO, REGISTERS::STANDARD_32::R R_FROM);

  void ret();

  VOID_FUNCTION compile();
private:
  std::vector<char> base;
  std::vector<std::pair<void*, size_t>> functions;

  void OP_SIZE_64_STANDARD();
  void OP_SIZE_64_ADDITIONAL();
};

#endif