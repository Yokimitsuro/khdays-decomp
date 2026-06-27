extern void func_0203c7e8(void);
extern void func_ov107_020c9eac(void);
extern void func_0203d194(void);
extern void func_ov107_020c68ec(void);

asm void func_ov242_020d3c64(void)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    ldr     r0, [r5, #0x384]
    bl      func_0203c7e8
    ldr     r0, [r5, #0x39c]
    bl      func_ov107_020c9eac
    ldr     r0, [r5, #0x388]
    bl      func_0203c7e8
    ldr     r0, [r5, #0x3a0]
    bl      func_0203c7e8
    mov     r4, #0
_L_002c:
    add     r0, r5, r4, lsl #2
    ldr     r0, [r0, #0x38c]
    bl      func_0203c7e8
    add     r4, r4, #1
    cmp     r4, #3
    blt     _L_002c
    ldr     r0, [r5, #0x3a4]
    cmp     r0, #0
    beq     _L_005c
    bl      func_0203d194
    mov     r0, #0
    str     r0, [r5, #0x3a4]
_L_005c:
    mov     r0, r5
    bl      func_ov107_020c68ec
    ldmfd   sp!, {r3, r4, r5, pc}
}
