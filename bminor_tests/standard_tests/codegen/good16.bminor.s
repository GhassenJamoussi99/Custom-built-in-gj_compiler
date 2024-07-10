.intel_syntax noprefix

.text  # Start the code section

.globl main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    lea rdi, L0
    lea rax, str
    mov rsi, rax
    call printf
    # Allocate space for local variable str2
    lea rdi, L1
    mov qword ptr [rbp-8], rbx
    lea rdi, L2
    lea rbx, [rbp-8]
    mov rsi, rbx
    call printf
    leave
    ret

.data
str:
	.string "hello"
L0:
	.string "%s\n"
L1:
	.string " world"
L2:
	.string "%s\n"

