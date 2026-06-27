extern void func_0201cb3c(void *p, int x);
extern int *data_0204c234;

asm void func_02033fb4(int idx, int flag)
{
    stmdb sp!, {r3, lr}
    ldr   lr, =data_0204c234
    ldr   ip, =0xb44bc
    ldr   r3, [lr]
    mov   r2, #0
    add   r3, r3, #0xb4000
    strb  r1, [r3, #0x7b7]
    ldr   r3, [lr]
    add   r3, r3, ip
    add   r0, r3, r0, lsl #2
    bl    func_0201cb3c
    ldmia sp!, {r3, pc}
}
