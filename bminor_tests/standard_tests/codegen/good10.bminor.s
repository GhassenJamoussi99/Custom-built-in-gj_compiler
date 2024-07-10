.intel_syntax noprefix

.text  # Start the code section

.globl main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    lea rdi, L0
    mov rax, x
    mov rsi, rax
    call printf
    mov rbx, 0
    mov rax, rbx
    leave
    ret

.data
x:
	.quad 10
L0:
	.string "%d\n"

