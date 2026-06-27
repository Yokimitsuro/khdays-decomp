extern void func_02023930(void);
extern int data_ov098_020bbce0;

asm void func_ov098_020bbc18(void)
{
    ldr r12, =func_02023930
    mov r1, r0
    ldr r0, =data_ov098_020bbce0
    bx r12
}
