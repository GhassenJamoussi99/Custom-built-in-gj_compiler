.intel_syntax noprefix

.text  # Start the code section

.globl test
test:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    mov rax, [rbp + 24]
    mov rbx, [rbp + 32]
    add rax, rbx
    mov rax, rax
    leave
    ret

.globl main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    mov rax, 0
    mov [rbp-8], rax
    lea rdi, L0
    call printf
L1:
    mov rbx, [rbp-8]
    mov rcx, 30
    cmp rbx, rcx
    setl al
    movzx rbx, al
cmp rbx, 0
je L2
    lea rdi, L3
    mov rbx, [rbp-8]
    mov rcx, [rbp-8]
    push rcx
    push rbx
    push rax
    call test
    mov rbx, rax
    pop rax
    add rsp, 16
    mov rsi, rbx
    call printf
    mov rcx, [rbp-8]
    mov rdx, 1
    add rcx, rdx
    mov [rbp-8], rcx
jmp L1
L2:
    mov rcx, 0
    mov rax, rcx
    leave
    ret

.data
L0:
	.string "Numbers\n"
L3:
	.string "%d\n"

