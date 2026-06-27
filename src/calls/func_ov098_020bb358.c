extern void func_ov022_02091228(void *r0);
extern void NNSi_FndFreeFromDefaultHeap(void *r0);
extern void func_0202a7dc(void *r0);
extern char data_ov098_020bbda0[];

asm void func_ov098_020bb358(void *r0)
{
    stmfd   sp!, {r3, r4, r5, lr}
    ldr     r1, [pc, #0x58]
    mov     r4, r0
    add     r0, r4, #0x2000
    ldr     r1, [r1]
    ldr     r0, [r0, #0x644]
    add     r1, r1, #0x2c
    add     r5, r1, #0x2c00
    bl      func_ov022_02091228
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    add     r0, r0, #0x30
    bl      func_ov022_02091228
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    bl      NNSi_FndFreeFromDefaultHeap
    add     r5, r5, #0x18
    mov     r4, #0
_L_loop:
    mov     r0, r5
    bl      func_0202a7dc
    add     r4, r4, #1
    cmp     r4, #7
    add     r5, r5, #0x10c
    blt     _L_loop
    ldmfd   sp!, {r3, r4, r5, pc}
    dcd     data_ov098_020bbda0
}
