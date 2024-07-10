.intel_syntax noprefix
.data
x:
   .quad 5

.text  # Start the code section


.globl main
main:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    mov rax, 10
    mov rax, rax
    leave
    ret
