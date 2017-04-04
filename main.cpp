#include "main.hpp"
#include "isa/stack_machine.hpp"

using namespace REGISTERS;

int main() {
    int a = 2;
    int b = 1;
    int c;

    stack_machine m;

    m.push(&a);
    m.push(&b);
    m.push(&b);

    m.add();
    m.add();

    m.store(&c);

    VOID_FUNCTION f = m.compile();

    f();

    std::cout << c << std::endl;

    return 0;
}
