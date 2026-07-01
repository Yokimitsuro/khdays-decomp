extern void func_0202a7dc(void);
extern void func_ov022_02091228(void);
extern void NNSi_FndFreeFromDefaultHeap(void);
extern char data_ov102_020bb920[];

asm void func_ov102_020bae54(void *self)
{
    stmdb   sp!, {r4, lr}
    ldr     r1, =data_ov102_020bb920
    mov     r4, r0
    ldr     r0, [r1]
    add     r0, r0, #0x64
    add     r0, r0, #0x2c00
    bl      func_0202a7dc
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    blx     func_ov022_02091228
    add     r0, r4, #0x2000
    ldr     r0, [r0, #0x644]
    bl      NNSi_FndFreeFromDefaultHeap
    ldmia   sp!, {r4, pc}
}
