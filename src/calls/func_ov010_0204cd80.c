extern int *NNSi_FndGetCurrentRootHeap(void);
extern int OS_IsThreadAvailable_0x02023650(void);
extern void func_0202362c(int);
extern void func_0202f9ec(int *);
extern void func_0202f818(int *);
extern void NNSi_FndFreeFromDefaultHeap(int);
extern void func_02003948(int);

asm void func_ov010_0204cd80(void)
{
    stmfd   sp!, {r3, r4, r5, lr}
    bl      NNSi_FndGetCurrentRootHeap
    mov     r4, r0
    bl      OS_IsThreadAvailable_0x02023650
    mov     r5, r0
    mov     r0, #0
    bl      func_0202362c
    ldr     r0, [r4]
    cmp     r0, #0
    beq     _skip
    add     r0, r4, #0x18
    bl      func_0202f9ec
    add     r0, r4, #0xc
    bl      func_0202f818
    ldr     r0, [r4]
    bl      NNSi_FndFreeFromDefaultHeap
    mov     r0, #0
    str     r0, [r4]
_skip:
    mov     r0, r5
    bl      func_0202362c
    mvn     r0, #1
    bl      func_02003948
    ldmfd   sp!, {r3, r4, r5, pc}
}
