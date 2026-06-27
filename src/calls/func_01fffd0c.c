/* func_01fffd0c (ITCM, ARM): iterate intrusive double-linked list at &ctx[+4..]
 * with sentinel at ctx+0x10; find node whose [+0xc] == key (r1); when found,
 * unlink (write prev->next=next, next->prev=prev), call func_0203d194 with
 * node ptr aux, decrement ctx[+0x20], return 1. If iterated to sentinel,
 * return 0. Paired with func_0203c424 drain caller.
 */
extern void func_0203d194(void *p);

asm int func_01fffd0c(void *ctx, int key)
{
    stmdb sp!, {r4, lr}
    mov   r4, r0
    ldr   r0, [r4, #4]
    add   r3, r4, #0x10
    cmp   r0, r3
    beq   ret0
loop:
    ldr   r2, [r0, #0xc]
    cmp   r2, r1
    bne   advance
    ldmia r0, {r1, r2}
    str   r2, [r1, #4]
    ldr   r2, [r0]
    ldr   r1, [r0, #4]
    str   r2, [r1]
    bl    func_0203d194
    ldr   r1, [r4, #0x20]
    mov   r0, #1
    sub   r1, r1, #1
    str   r1, [r4, #0x20]
    ldmia sp!, {r4, pc}
advance:
    ldr   r0, [r0, #4]
    cmp   r0, r3
    bne   loop
ret0:
    mov   r0, #0
    ldmia sp!, {r4, pc}
}
