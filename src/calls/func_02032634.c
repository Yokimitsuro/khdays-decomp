/* func_02032634 (ARM): per-slot dispatcher; slot stride = 0x8c bytes.
 *   if (slot < 0) return;
 *   h = func_02031c30(ctx[+0x78 + slot*0x8c]);
 *   p = func_02011840(h->[+0x10], (u16)arg);
 *   func_02012480(&ctx[+0x18 + slot*0x8c], p);
 */
extern void *func_02031c30(void *h);
extern void *func_02011840(void *a, int b);
extern void  func_02012480(void *dst, void *p);

asm void func_02032634(void *ctx, int slot, int arg)
{
    stmdb sp!, {r4, r5, r6, lr}
    mov   r6, r0
    mov   r5, r2
    cmp   r1, #0
    ldmltia sp!, {r4, r5, r6, pc}
    mov   r2, #0x8c
    mul   r4, r1, r2
    add   r1, r6, r4
    ldr   r1, [r1, #0x78]
    bl    func_02031c30
    mov   r1, r5, lsl #0x10
    ldr   r0, [r0, #0x10]
    mov   r1, r1, lsr #0x10
    bl    func_02011840
    add   r2, r6, #0x18
    mov   r1, r0
    add   r0, r2, r4
    bl    func_02012480
    ldmia sp!, {r4, r5, r6, pc}
}
