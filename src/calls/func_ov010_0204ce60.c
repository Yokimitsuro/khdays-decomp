extern int *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov010_0204cddc(int a, int b, int c);
extern int func_ov010_0204ce20(void);
extern void func_0202fa20(int a, int b);
extern void func_0202fa38(int a, int b, int c, int d, int e, int f);
extern void func_0202f9f8(int a);

asm int func_ov010_0204ce60(void)
{
    stmfd   sp!, {r4, lr}
    sub     sp, sp, #8
    bl      NNSi_FndGetCurrentRootHeap
    mov     r4, r0
    ldr     r0, [r4, #0x78]
    cmp     r0, #4
    addls   pc, pc, r0, lsl #2
    b       _Lc8
    b       _L34
    b       _L50
    b       _L64
    b       _L9c
    b       _Lb8
_L34:
    mov     r0, #0x10000
    mov     r1, #0
    mov     r2, #0xc8
    bl      func_ov010_0204cddc
    mov     r0, #1
    str     r0, [r4, #0x78]
    b       _Lc8
_L50:
    bl      func_ov010_0204ce20
    cmp     r0, #0
    movne   r0, #2
    strne   r0, [r4, #0x78]
    b       _Lc8
_L64:
    ldr     r1, =0x04000130
    ldr     r0, =0x027fffa8
    ldrh    r2, [r1]
    ldrh    r1, [r0]
    ldr     r0, =0x00002fff
    orr     r1, r2, r1
    eor     r1, r1, r0
    and     r0, r1, r0
    mov     r0, r0, lsl #0x10
    mov     r0, r0, lsr #0x10
    tst     r0, #1
    movne   r0, #3
    strne   r0, [r4, #0x78]
    b       _Lc8
_L9c:
    mov     r0, #0
    sub     r1, r0, #0x10000
    mov     r2, #0x3e8
    bl      func_ov010_0204cddc
    mov     r0, #4
    str     r0, [r4, #0x78]
    b       _Lc8
_Lb8:
    bl      func_ov010_0204ce20
    cmp     r0, #0
    movne   r0, #5
    strne   r0, [r4, #0x78]
_Lc8:
    add     r0, r4, #0x18
    mov     r1, #0
    bl      func_0202fa20
    ldr     r1, =0x412
    add     r0, r4, #0x18
    str     r1, [sp]
    ldr     r12, [r4, #0x74]
    mov     r1, #0x80
    mov     r2, #0x60
    mov     r3, #1
    str     r12, [sp, #4]
    bl      func_0202fa38
    add     r0, r4, #0x18
    bl      func_0202f9f8
    ldr     r0, [r4, #0x78]
    cmp     r0, #5
    mvneq   r0, #1
    movne   r0, #0
    add     sp, sp, #8
    ldmfd   sp!, {r4, pc}
}
