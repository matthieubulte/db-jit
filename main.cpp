#include "main.hpp"

int main() {
    int page_size = getpagesize();

    int a = 2;
    int b = 1;
    int c;

    code_emitter emitter(page_size);

    MOV<RAX>(&emitter, (uint64_t)&a);
    MOV_FROM_REGISTER_AS_MEMORY<EBX, RAX>(&emitter);
    MOV<RAX>(&emitter, (uint64_t)&b);
    MOV_FROM_REGISTER_AS_MEMORY<ECX, RAX>(&emitter);
    MOV<RAX>(&emitter, (uint64_t)&b);
    MOV_FROM_REGISTER_AS_MEMORY<EDX, RAX>(&emitter);

    ADD<EBX, ECX>(&emitter);
    ADD<EBX, EDX>(&emitter);

    MOV<RAX>(&emitter, (uint64_t)&c);

    MOV_TO_REGISTER_AS_MEMORY<RAX, EBX>(&emitter);

    RET(&emitter);

    // Run it
    void *mem = mmap(NULL, page_size,
                     PROT_READ | PROT_WRITE,
                     MAP_ANON | MAP_PRIVATE,
                     -1, 0);


    memcpy(mem, emitter.get(), emitter.length());
    mprotect(mem, page_size, PROT_READ | PROT_EXEC);

    ((void (*) ())mem)();

    munmap(mem, page_size);
    // End run it

    std::cout << c << std::endl;

    return 0;
}
