.intel_syntax noprefix

.text  # Start the code section

.globl fxnCall
fxnCall:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    mov rax, x
    mov rbx, 4
    imul rax, rbx
    mov rax, rax
    leave
    ret

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
    push rax
    call fxnCall
    mov rbx, rax
    pop rax
    sub rax, rbx
    mov rax, rax
    leave
    ret

.data
x:
	.quad 5

