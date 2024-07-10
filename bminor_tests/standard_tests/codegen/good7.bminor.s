.intel_syntax noprefix

.text  # Start the code section

.globl main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    # Allocate space for local variable y
    mov rax, 2
    mov [rbp-8], rax

    mov rax, x
    mov rbx, 10
    add rax, rbx
    mov rbx, [rbp-8]
    imul rax, rbx
    mov rbx, x
    mov rcx, 4
    imul rbx, rcx
    sub rax, rbx
    mov rax, rax
    leave
    ret

.data
x:
	.quad 5

