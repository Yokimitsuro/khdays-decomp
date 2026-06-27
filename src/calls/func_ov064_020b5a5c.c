extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_0202a7dc(void *arg);
extern void func_ov064_020b6978(void *arg);
extern void func_ov022_0209fab4(void *arg);
extern int *data_ov064_020b7420;

asm void func_ov064_020b5a5c(void)
{
    push    {r4, lr}
    bl      NNSi_FndGetCurrentRootHeap
    mov     r4, r0
    ldr     r0, =0x2c2c
    ldr     r1, [r4, r0]
    cmp     r1, #0
    beq     _no_free
    add     r0, r0, #4
    add     r0, r4, r0
    bl      func_0202a7dc
    ldr     r0, =0x2c2c
    mov     r1, #0
    str     r1, [r4, r0]
_no_free:
    mov     r0, r4
    bl      func_ov064_020b6978
    mov     r0, r4
    bl      func_ov022_0209fab4
    ldr     r0, =data_ov064_020b7420
    mov     r1, #0
    str     r1, [r0]
    pop     {r4, pc}
}
