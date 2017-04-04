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

class code_emitter {
public:

  code_emitter(int size) {
    base = std::unique_ptr<char[]>(new char[size]);
  }

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

  unsigned long length();
  char* get();

  VOID_FUNCTION compile();
private:
  size_t offset = 0;
  std::unique_ptr<char[]> base;
  std::vector<std::pair<void*, size_t>> functions;
};

#endif