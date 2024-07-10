.intel_syntax noprefix

.text  # Start the code section

.globl main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    mov rax, x
    mov rbx, x
    add rax, rbx
    mov rax, rax
    leave
    ret

.data
x:
	.quad 5

