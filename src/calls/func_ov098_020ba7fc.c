extern void NNSi_FndGetCurrentRootHeap(void);
extern void func_ov098_020bb358(void);
extern void func_ov022_0209fab4(void *);
extern int data_ov098_020bbda0;

asm void func_ov098_020ba7fc(void)
{
    push {r4, lr}
    bl NNSi_FndGetCurrentRootHeap
    add r4, r0, #0
    bl func_ov098_020bb358
    add r0, r4, #0
    bl func_ov022_0209fab4
    ldr r0, =data_ov098_020bbda0
    mov r1, #0
    str r1, [r0]
    pop {r4, pc}
}
