extern void MI_Copy48B(void);
extern void func_02016b60(void);
extern void func_01ff9f00(void);
extern void func_0201571c(void);
extern void func_020279e0(void);

asm void func_ov070_020b8b40(void)
{
    stmfd   sp!, {r4, r5, lr}
    sub     sp, sp, #0xc
    mov     r4, r1
    ldr     r1, [r4, #4]
    mov     r5, r2
    cmp     r1, #6
    addls   pc, pc, r1, lsl #2
    b       _end
    b       _end
    b       _case_3c
    b       _case_3c
    b       _case_3c
    b       _case_3c
    b       _end
    b       _case_3c
_case_3c:
    ldr     r1, [r4]
    cmp     r1, #0
    beq     _c0
    cmp     r1, #1
    beq     _c1
    b       _after
_c0:
    add     r0, r0, #0x128
    add     r0, r0, #0x400
    add     r1, r4, #0x88
    bl      MI_Copy48B
    b       _after
_c1:
    add     r0, r0, #0x158
    add     r0, r0, #0x400
    add     r1, r4, #0x88
    bl      MI_Copy48B
_after:
    ldr     r0, [r4, #0x80]
    add     r2, r5, #5
    mov     r1, #2
    bl      func_02016b60
    ldr     r0, [r4, #0x2c]
    add     r1, sp, #0
    ldr     r3, [r0, #0x1c]
    mov     r0, #0x1b
    mov     r2, #3
    str     r3, [sp]
    str     r3, [sp, #4]
    str     r3, [sp, #8]
    bl      func_01ff9f00
    bl      func_0201571c
    add     r1, r4, #0x88
    mov     r0, #0x17
    mov     r2, #0xc
    bl      func_01ff9f00
    add     r0, r4, #0x28
    bl      func_020279e0
_end:
    add     sp, sp, #0xc
    ldmfd   sp!, {r4, r5, pc}
}
