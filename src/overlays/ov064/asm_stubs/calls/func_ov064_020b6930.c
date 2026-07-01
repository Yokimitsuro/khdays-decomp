extern void func_0202a634(void *arg0, int arg1, int arg2, int arg3);
extern void func_ov064_020b6f6c(void *arg);
extern int data_ov064_020b73f4;

asm void func_ov064_020b6930(void *arg)
{
    stmdb   sp!, {r4, lr}
    mov     r4, r0
    add     r0, r4, #0xdf0
    add     r3, r0, #0x2000
    add     r0, r4, #0x2000
    mov     r1, #0
    strb    r1, [r0, #0xdf0]
    str     r1, [r3, #0x114]
    ldrb    r2, [r4, #9]
    ldr     r1, =data_ov064_020b73f4
    add     r0, r3, #4
    add     r3, r2, #7
    mov     r2, #1
    bl      func_0202a634
    mov     r0, r4
    bl      func_ov064_020b6f6c
    ldmia   sp!, {r4, pc}
}
