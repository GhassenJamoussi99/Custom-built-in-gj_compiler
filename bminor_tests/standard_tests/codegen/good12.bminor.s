.intel_syntax noprefix

.text  # Start the code section

.globl main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    # Allocate space for local variable y
    mov rax, 10
    mov [rbp-8], rax

    # Allocate space for local variable z
    mov rax, 5
    mov [rbp-16], rax

    mov rax, x
    mov rbx, [rbp-16]
    cmp rax, rbx
    setge al
    movzx rax, al
    cmp rax, 0
    je L0
    lea rdi, L2
    call printf
    jmp L1
  L0:
    lea rdi, L3
    call printf
  L1:
    mov rcx, [rbp-8]
    mov rdx, x
    cmp rcx, rdx
    setg al
    movzx rcx, al
    cmp rcx, 0
    je L4
    lea rdi, L6
    call printf
    jmp L5
  L4:
    lea rdi, L7
    call printf
  L5:
    mov rsi, [rbp-16]
    mov rdi, x
    cmp rsi, rdi
    sete al
    movzx rsi, al
    cmp rsi, 0
    je L8
    lea rdi, L10
    call printf
    jmp L9
  L8:
    lea rdi, L11
    call printf
  L9:
    mov r8, x
    mov r9, [rbp-8]
    cmp r8, r9
    setle al
    movzx r8, al
    cmp r8, 0
    je L12
    lea rdi, L14
    call printf
    jmp L13
  L12:
    lea rdi, L15
    call printf
  L13:
    mov r10, x
    mov r11, [rbp-8]
    cmp r10, r11
    setne al
    movzx r10, al
    cmp r10, 0
    je L16
    lea rdi, L18
    call printf
    jmp L17
  L16:
    lea rdi, L19
    call printf
  L17:
    mov r12, 0
    mov rax, r12
    leave
    ret

.data
x:
	.quad 5
L2:
	.string "x \>= z\n"
L3:
	.string "shouldn't be printed\n"
L6:
	.string "y \> x\n"
L7:
	.string "shouldn't be printed\n"
L10:
	.string "z == x\n"
L11:
	.string "shouldn't be printed\n"
L14:
	.string "x \<= y\n"
L15:
	.string "shouldn't be printed\n"
L18:
	.string "x != y\n"
L19:
	.string "shouldn't be printed\n"

