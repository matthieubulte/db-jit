#include "stack_machine.hpp"

void stack_machine::push(void* address) {
  if(stack_pointer <= 4) {
    emitter.move(REGISTERS::STANDARD_64::RAX, (uint64_t)address);
    emitter.move(available_register[stack_pointer], REGISTERS::MEMORY_ACCESS(REGISTERS::STANDARD_64::RAX));
    stack_pointer++;
  }
}

void stack_machine::add() {
  if (stack_pointer > 1) {
    emitter.add(available_register[stack_pointer - 2], available_register[stack_pointer - 1]);
    stack_pointer--;
  }
}

void stack_machine::store(void* address) {
  if(stack_pointer > 0) {
    emitter.move(REGISTERS::STANDARD_64::RAX, (uint64_t)address);
    emitter.move(REGISTERS::MEMORY_ACCESS(REGISTERS::STANDARD_64::RAX), available_register[stack_pointer - 1]);
    stack_pointer--;
  }
}

VOID_FUNCTION stack_machine::compile() {
  emitter.ret();
  return emitter.compile();
}

