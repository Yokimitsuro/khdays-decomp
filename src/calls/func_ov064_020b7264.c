extern void func_02023930(void);
extern int data_ov064_020b7380;

asm void func_ov064_020b7264(void *arg)
{
    ldr     ip, =func_02023930
    mov     r1, r0
    ldr     r0, =data_ov064_020b7380
    bx      ip
}
