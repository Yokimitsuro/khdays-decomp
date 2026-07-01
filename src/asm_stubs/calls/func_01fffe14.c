/* func_01fffe14 (ITCM, ARM): irq/sound polling.
 *   ptr = (data_ov022_020b2e78)->[+4];
 *   if (!ptr) return 0;
 *   if (ptr->flags & 2) tail-call func_02030788() (still pops r3,lr);
 *   else if (data_0204be04 byte != 0 && ptr->[+0x10] != 0) return 1; else 0.
 */
extern int func_02030788(void);
extern void *data_ov022_020b2e78;
extern char data_0204be04;

asm int func_01fffe14(void)
{
    stmdb sp!, {r3, lr}
    ldr   r0, =data_ov022_020b2e78
    ldr   r1, [r0, #4]
    cmp   r1, #0
    moveq r0, #0
    ldmeqia sp!, {r3, pc}
    ldr   r0, [r1]
    tst   r0, #2
    bne   tail
    ldr   r0, =data_0204be04
    ldrb  r0, [r0]
    cmp   r0, #0
    ldrne r0, [r1, #0x10]
    cmpne r0, #0
    movne r0, #1
    moveq r0, #0
    ldmia sp!, {r3, pc}
tail:
    bl    func_02030788
    ldmia sp!, {r3, pc}
}
