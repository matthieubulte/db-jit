#ifndef DB_JIT_STACK_MACHINE_H
#define DB_JIT_STACK_MACHINE_H

#include "code_emitter.hpp"

class stack_machine {
private:
  code_emitter emitter;
  REGISTERS::STANDARD_32 available_register[5] = {
      REGISTERS::STANDARD_32::ECX,
      REGISTERS::STANDARD_32::EDX,
      REGISTERS::STANDARD_32::EBX,
      REGISTERS::STANDARD_32::ESI,
      REGISTERS::STANDARD_32::EDI
  };
  unsigned short stack_pointer = 0;
public:
  stack_machine() { }

  void push(void* address);
  void add();
  void store(void* address);

  VOID_FUNCTION compile();
};

#endif //DB_JIT_STACK_MACHINE_H
