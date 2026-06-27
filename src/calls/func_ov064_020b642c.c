extern int *data_ov064_020b7420;
extern void func_ov022_020a35f4(void *arg, int value);

asm void func_ov064_020b642c(void *arg, int value)
{
    ldr     r2, =data_ov064_020b7420
    ldr     ip, =func_ov022_020a35f4
    ldr     r2, [r2]
    mov     r3, #0
    add     r2, r2, #0xdf0
    add     r2, r2, #0x2000
    str     r1, [r2, #0x114]
    mov     r1, #0x21
    str     r3, [r2, #0x118]
    bx      ip
}
