#include "main.hpp"
#include "isa/stack_machine.hpp"

using namespace REGISTERS;

#define STR1(x) #x
#define STR(x) STR1(x)
#define N 10

int main() {

    int as[N];
    int cs[N];
    
    code_emitter ce;

    ce.move(STANDARD_32::EDI,
	    MEMORY_ACCESS(STANDARD_64::RBX));

    ce.move(MEMORY_ACCESS(STANDARD_64::RDX),
	    STANDARD_32::EDI);

    ce.ret();
    
    VOID_FUNCTION f = ce.compile();
    
    for (int i = 0; i < N; i++) {
      as[i] = i;
    }

    asm volatile (
	".intel_syntax\n"
	"mov %%rbx,%0\n"
	"mov %%rdx,%1\n"

	"xor %%eax, %%eax\n"
	
	"start:\n"

	"call %2\n"
	
	"add %%rbx,4\n"
	"add %%rdx,4\n"

	"inc %%eax\n"
	"cmp %%eax," STR(N) "\n"
	"jne start\n"
	".att_syntax\n"
	:
	: "r"(&as[0]), "r"(&cs[0]), "r"(f)
    );
    // note: asm passes the arguments using registers, be carefull
    // note': anyway this code will get generated in the future
    
    for (int i = 0; i < N; i++) {
      assert(as[i] == cs[i]);
    }

    
    return 0;
}
