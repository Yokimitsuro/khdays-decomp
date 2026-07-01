extern int SND_RegisterSeq(int a, int b);
extern void func_0202a4d0(void *a, int b, int c, int d);

asm void func_0202a6a0(void *a, int b, int c, int d)
{
    stmdb sp!, {r4, r5, r6, lr}
    mov r4, r3
    mov r6, r0
    mov r0, r1
    mov r5, r2
    mov r1, r4
    bl SND_RegisterSeq
    str r0, [r6, #0x74]
    mov r0, r6
    mov r1, r5
    mov r3, r4
    mov r2, #0
    bl func_0202a4d0
    ldmia sp!, {r4, r5, r6, pc}
}
