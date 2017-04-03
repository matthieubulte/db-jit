#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <cstring>
#include <cstdarg>

class code_emiter {
public:
    code_emiter(char* base) : base(base) {}

    void write_byte(char b) {
        base[offset++] = b;
    }

    void write_bytes(int argc, const char* bytes) {
        for (int i = 0; i < argc; i++) {
            write_byte(bytes[i]);
        }
    }
    
    void write_ptr(int* address) {
        char* ptr_addr = (char*)&address;
        write_byte(ptr_addr[0]);
        write_byte(ptr_addr[1]);
        write_byte(ptr_addr[2]);
        write_byte(ptr_addr[3]);
        write_byte(ptr_addr[4]);
        write_byte(ptr_addr[5]);
        write_byte(ptr_addr[6]);
        write_byte(ptr_addr[7]);
    }

    void load_rax(int* ptr) {
        const char mov_rax[] = "\x48\xb8";
        write_bytes(2, mov_rax);
        write_ptr(ptr);
    }

    void push_ptr(int* ptr) {
        load_rax(ptr);
        write_bytes(load_rax_len[current_register],
                    &load_rax_table[load_rax_offsets[current_register]]);
        current_register++;
    }

    void pop_add() {
        current_register--;
        write_bytes(pop_add_len[current_register-1],
                    &pop_add_table[pop_add_offsets[current_register-1]]);
    }

    void ret() {
        write_byte('\xc3');
    }

    unsigned long length() { return offset; }

    char* get() { return base; }
private:
    unsigned long offset = 0;
    char* base;

    int current_register = 0;

    const int load_rax_offsets[11] = {0, 2, 4, 6, 9, 12, 15, 18, 21, 23, 26};
    const int load_rax_len[11] = {2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3};
    const char load_rax_table[31] = "\x8B\x18\x8B\x08\x8B\x10\x44\x8B\x00\x44\x8B\x08\x44\x8B\x10\x44\x8B\x18\x44\x8B\x20\x44\x8B\x28\x44\x8B\x30\x44\x8B\x38";

    const int pop_add_offsets[10] = {0, 2, 4, 7, 10, 13, 16, 19, 22, 25};
    const int pop_add_len[10] = {2, 2, 3, 3, 3, 3, 3, 3, 3, 3};
    const char pop_add_table[29] = "\x01\xCB\x01\xD1\x44\x01\xC2\x45\x01\xC8\x45\x01\xD1\x45\x01\xDA\x45\x01\xE3\x45\x01\xEC\x45\x01\xF5\x45\x01\xFE";

};


int main() {
    size_t page_size = getpagesize();

    int a = 2;
    int b = 1;
    int c;

    char shellcode[page_size];
    code_emiter emiter(shellcode);

    emiter.push_ptr(&a);
    emiter.push_ptr(&b);
    emiter.push_ptr(&b);
    emiter.pop_add();
    emiter.pop_add();

    emiter.load_rax(&c);

    const char write_ebx_rax[] = "\x89\x18";
    emiter.write_bytes(sizeof(write_ebx_rax) - 1, write_ebx_rax);

    emiter.ret();

    // Run it
    void *mem = mmap(NULL, page_size,
                     PROT_READ | PROT_WRITE,
                     MAP_ANON | MAP_PRIVATE,
                     -1, 0);


    memcpy(mem, emiter.get(), emiter.length());
    mprotect(mem, page_size, PROT_READ | PROT_EXEC);

    ((void (*)())mem)();

    munmap(mem, page_size);
    // End run it

    std::cout << c << std::endl;

    return 0;
}
