#include "instructions.hpp"

void OP_SIZE_64_STANDARD(code_emitter *e) {
  e->write_byte('\x48');
}

void OP_SIZE_64_ADDITIONAL(code_emitter *e) {
  e->write_byte('\x49');
}

void RET(code_emitter *e) {
  e->write_byte('\xc3');
}