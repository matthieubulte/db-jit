#ifndef DB_JIT_CODE_EMITTER_H
#define DB_JIT_CODE_EMITTER_H

#include <cstdint>
#include <memory>

class code_emitter {
public:
  code_emitter(int size) {
    base = std::unique_ptr<char[]>(new char[size]);
  }

  void write_byte(unsigned char b);
  void write_bytes(int argc, const unsigned char* bytes);
  void write_imm(uint16_t imm);
  void write_imm(uint32_t imm);
  void write_imm(uint64_t imm);

  /*void load_rax(int* ptr) {
    const char mov_rax[] = "\x48\xb8";
    write_bytes(2, mov_rax);
    write_ptr(ptr);
  }*/

  unsigned long length();
  char* get();
private:
  unsigned long offset = 0;

  std::unique_ptr<char[]> base;

  int current_register = 0;

  const int load_rax_offsets[11] = {0, 2, 4, 6, 9, 12, 15, 18, 21, 23, 26};
  const int load_rax_len[11] = {2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3};
  const char load_rax_table[31] = "\x8B\x18\x8B\x08\x8B\x10\x44\x8B\x00\x44\x8B\x08\x44\x8B\x10\x44\x8B\x18\x44\x8B\x20\x44\x8B\x28\x44\x8B\x30\x44\x8B\x38";

  const int pop_add_offsets[10] = {0, 2, 4, 7, 10, 13, 16, 19, 22, 25};
  const int pop_add_len[10] = {2, 2, 3, 3, 3, 3, 3, 3, 3, 3};
  const char pop_add_table[29] = "\x01\xCB\x01\xD1\x44\x01\xC2\x45\x01\xC8\x45\x01\xD1\x45\x01\xDA\x45\x01\xE3\x45\x01\xEC\x45\x01\xF5\x45\x01\xFE";

};

#endif