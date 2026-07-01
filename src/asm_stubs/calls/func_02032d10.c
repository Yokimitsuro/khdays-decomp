/* func_02032d10 (ARM): big-offset accessor.
 *   base = *data_0204c234;
 *   base[0xb46fc/0xb479e/0xb479c whatever +0xb4000/+0x6fc] = 1 (byte set);
 *   base[+0xb46f6]_h = (u16)arg;
 *   func_0201b8e4((base + 0xb04b4)->[0]);
 *   func_0201f70c((base + 0xb04b4)->[0], (u16)arg, base + 0xb46fc);
 */
extern void func_0201b8e4(void *p);
extern void func_0201f70c(void *p, int q, void *r);
extern void *data_0204c234;

asm void func_02032d10(int arg)
{
    stmdb sp!, {r3, r4, r5, lr}
    ldr   r1, =data_0204c234
    mov   r3, #1
    ldr   r4, [r1]
    ldr   r2, =0x000b46f6
    add   r1, r4, #0xb4000
    mov   r5, r0
    strb  r3, [r1, #0x6fc]
    strh  r5, [r4, r2]
    add   r0, r4, #0xb0000
    ldr   r0, [r0, #0x4b4]
    bl    func_0201b8e4
    add   r1, r4, #0xb0000
    ldr   r2, =0x000b46fc
    mov   r0, r5, lsl #0x10
    ldr   r1, [r1, #0x4b4]
    mov   r0, r0, lsr #0x10
    add   r2, r4, r2
    bl    func_0201f70c
    ldmia sp!, {r3, r4, r5, pc}
}
