extern void func_0203d15c(void);
extern void OS_SPrintf(void);
extern void func_ov107_020c9c24(void);
extern void func_ov107_020c6624(void);
extern int data_ov286_020d4580;
extern void func_ov286_020d3844(void);

asm void func_ov286_020d37b8(int arg)
{
    stmfd   sp!, {r3, r4, r5, lr}
    sub     sp, sp, #0x20
    mov     r5, r0
    add     r2, sp, #0
    mov     r0, #7
    mov     r1, #0
_loop:
    strb    r1, [r2]
    strb    r1, [r2, #1]
    strb    r1, [r2, #2]
    strb    r1, [r2, #3]
    add     r2, r2, #4
    subs    r0, r0, #1
    bne     _loop
    mov     r0, #0x390
    strb    r1, [r2]
    bl      func_0203d15c
    mov     r4, r0
    mov     r2, #0x6a
    ldr     r1, =data_ov286_020d4580
    add     r0, sp, #0
    strb    r2, [r4, #0x19c]
    bl      OS_SPrintf
    add     r0, sp, #0
    bl      func_ov107_020c9c24
    str     r0, [r4, #0x1a4]
    ldr     r2, =func_ov286_020d3844
    mov     r0, r4
    mov     r1, r5
    str     r2, [r4, #0x18c]
    bl      func_ov107_020c6624
    mov     r0, r4
    add     sp, sp, #0x20
    ldmfd   sp!, {r3, r4, r5, pc}
}
