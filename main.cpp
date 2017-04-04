#include "main.hpp"

using namespace REGISTERS;

int main() {
    int a = 2;
    int b = 1;
    int c;

    code_emitter emitter;

    emitter.move(STANDARD_64::R::RAX, (uint64_t)&a);
    emitter.move_from_register_as_memory(STANDARD_32::R::EBX, STANDARD_64::R::RAX);
    emitter.move(STANDARD_64::R::RAX, (uint64_t)&b);
    emitter.move_from_register_as_memory(STANDARD_32::R::ECX, STANDARD_64::R::RAX);
    emitter.move(STANDARD_64::R::RAX, (uint64_t)&b);
    emitter.move_from_register_as_memory(STANDARD_32::R::EDX, STANDARD_64::R::RAX);

    emitter.add(STANDARD_32::R::EBX, STANDARD_32::R::ECX);
    emitter.add(STANDARD_32::R::EBX, STANDARD_32::R::EDX);

    emitter.move(STANDARD_64::R::RAX, (uint64_t)&c);
    emitter.move_to_register_as_memory(STANDARD_64::R::RAX, STANDARD_32::R::EBX);
    emitter.ret();

    VOID_FUNCTION f = emitter.compile();

    f();

    std::cout << c << std::endl;

    return 0;
}
