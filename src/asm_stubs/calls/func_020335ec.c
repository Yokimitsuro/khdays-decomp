/* func_020335ec (ARM): notify-byte handler. Looks up *data_0204c234, reads a
 * signed half at large offset 0xb46f6; if it equals r4 (the byte arg) AND
 * the byte at [base + 0xb479e] == 1, falls through to "force-notify" path
 * which calls func_02032cbc(0); if returns nonzero and (*ret)==2, store r4
 * at ret[1] and return 1. Otherwise call func_02032be8(2, r4, 0). Always
 * returns 1.
 */
extern void *func_02032cbc(int x);
extern void  func_02032be8(int a, int b, int c);
extern void *data_0204c234;

asm int func_020335ec(int notify)
{
    stmdb sp!, {r4, lr}
    ldr   r2, =data_0204c234
    ldr   r1, =0x000b46f6
    ldr   r2, [r2]
    mov   r4, r0
    ldrsh r0, [r2, r1]
    cmp   r0, r4
    bne   force
    add   r0, r2, #0xb4000
    ldrb  r0, [r0, #0x79e]
    cmp   r0, #1
    bne   ret1
force:
    mov   r0, #0
    bl    func_02032cbc
    cmp   r0, #0
    beq   notify_default
    ldrb  r1, [r0]
    cmp   r1, #2
    beq   store_r4
notify_default:
    mov   r1, r4
    mov   r0, #2
    mov   r2, #0
    bl    func_02032be8
    b     ret1
store_r4:
    strb  r4, [r0, #1]
ret1:
    mov   r0, #1
    ldmia sp!, {r4, pc}
}
