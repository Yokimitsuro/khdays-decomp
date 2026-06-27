extern void func_0202a7dc(void);
extern void *data_ov053_020b7e60;

asm void func_ov053_020b790c(void)
{
    ldr     r0, =data_ov053_020b7e60
    ldr     r3, =func_0202a7dc
    ldr     r1, [r0, #0]
    ldr     r0, =0x2d0c
    add     r0, r1, r0
    bx      r3
}
