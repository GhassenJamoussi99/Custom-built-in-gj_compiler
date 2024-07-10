.intel_syntax noprefix

.text  # Start the code section

.globl main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    lea rdi, L0
    call printf
    mov rbx, 0
    mov rax, rbx
    leave
    ret

.data
L0:
	.string "hello world\n"

