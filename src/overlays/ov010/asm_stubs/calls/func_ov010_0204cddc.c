extern int *NNSi_FndGetCurrentRootHeap(void);
extern void func_02035f84(int);
extern void func_02035fb0(int, int, int, int, int);
extern void func_02035ffc(int);

asm void func_ov010_0204cddc(int a, int b, int c)
{
    stmfd   sp!, {r3, r4, r5, r6, r7, lr}
    mov     r7, r0
    mov     r6, r1
    mov     r5, r2
    bl      NNSi_FndGetCurrentRootHeap
    mov     r4, r0
    add     r0, r4, #0x58
    bl      func_02035f84
    str     r5, [sp]
    mov     r2, r7
    mov     r3, r6
    add     r0, r4, #0x58
    mov     r1, #0
    bl      func_02035fb0
    add     r0, r4, #0x58
    bl      func_02035ffc
    ldmfd   sp!, {r3, r4, r5, r6, r7, pc}
}
