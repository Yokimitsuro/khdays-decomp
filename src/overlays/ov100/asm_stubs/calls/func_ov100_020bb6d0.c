extern void func_0202a634(void);
extern void func_ov100_020bbd0c(void);
extern void data_ov100_020bc194(void);

asm void func_ov100_020bb6d0(void)
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
    ldr     r1, =data_ov100_020bc194
    add     r0, r3, #4
    add     r3, r2, #7
    mov     r2, #1
    bl      func_0202a634
    mov     r0, r4
    bl      func_ov100_020bbd0c
    ldmia   sp!, {r4, pc}
}
