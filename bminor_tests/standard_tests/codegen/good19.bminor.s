.intel_syntax noprefix

.text  # Start the code section

.globl fib
fib:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    mov rax, [rbp + 24]
    mov rbx, 1
    cmp rax, rbx
    setl al
    movzx rax, al
    cmp rax, 0
    je L0
    mov rax, 0
    mov rax, rax
    jmp L1
  L0:
    mov rax, [rbp + 24]
    mov rbx, 2
    cmp rax, rbx
    setl al
    movzx rax, al
    cmp rax, 0
    je L2
    mov rax, 1
    mov rax, rax
    jmp L3
  L2:
    mov rax, [rbp + 24]
    mov rbx, 1
    sub rax, rbx
    push rax
    push rax
    call fib
    mov rax, rax
    pop rax
    add rsp, 8
    mov rcx, [rbp + 24]
    mov rdx, 2
    sub rcx, rdx
    push rcx
    push rax
    call fib
    mov rcx, rax
    pop rax
    add rsp, 8
    add rax, rcx
    mov rax, rax
  L3:
  L1:
    leave
    ret

.globl main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    lea rdi, L4
    call printf
    mov rcx, 0
    mov [rbp-8], rcx
  L5:
    mov rcx, [rbp-8]
    mov rsi, 30
    cmp rcx, rsi
    setl al
    movzx rcx, al
    cmp rcx, 0
    je L6
    lea rdi, L7
    mov rcx, [rbp-8]
    push rcx
    push rax
    call fib
    mov rcx, rax
    pop rax
    add rsp, 8
    mov rsi, rcx
    call printf
    mov rsi, [rbp-8]
    mov rdi, 1
    add rsi, rdi
    mov [rbp-8], rsi
    jmp L5
  L6:
    mov rsi, 0
    mov rax, rsi
    leave
    ret

.data
L4:
	.string "Table of Fibonnacci Numbers\n"
L7:
	.string "%d\n"

