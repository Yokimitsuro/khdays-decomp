extern int func_0203c634(void *r0, int r1, int r2);
extern void func_ov295_020d3db4(void *p);

asm void func_ov295_020d3d74(void *r0)
{
    stmfd   sp!, {r3, lr}
    ldr     r1, [r0, #4]
    ldr     r2, =func_ov295_020d3db4
    ldr     ip, [r1]
    ldrh    r3, [ip, #0x60]
    mov     r1, r3, lsl #0x10
    mov     r1, r1, lsr #0x18
    orr     r1, r1, #0xde
    bic     r3, r3, #0xff00
    mov     r1, r1, lsl #0x18
    orr     r1, r3, r1, lsr #0x10
    strh    r1, [ip, #0x60]
    ldrsb   r1, [r0, #0x20]
    bl      func_0203c634
    ldmfd   sp!, {r3, pc}
}
