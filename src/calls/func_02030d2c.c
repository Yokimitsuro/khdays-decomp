extern int func_01fff99c(int x);
extern void func_01fffa60(void *a, int b, int c, int d);

asm void func_02030d2c(void *p, int arg1)
{
    stmdb sp!, {r3, r4, r5, lr}
    mov   r5, r0
    ldrh  r0, [r5]
    mov   r4, r1
    mov   r0, r0, lsl #0x1a
    mov   r0, r0, lsr #0x1b
    bl    func_01fff99c
    mov   r2, r0
    mov   r0, r5
    mov   r1, r4
    mov   r3, #0
    bl    func_01fffa60
    ldmia sp!, {r3, r4, r5, pc}
}
