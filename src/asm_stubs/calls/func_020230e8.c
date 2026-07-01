/* Thumb wrapper: forwards (data_0204be08->field_4 + 0xc) to func_02023448, then func_02032f5c.
 * Likely an OS subsystem init step (init thread/queue from a global ptr).
 */
extern void func_02023448(void *p);
extern void func_02032f5c(void);
extern void *data_0204be08;

asm void func_020230e8(void)
{
    push  {r3, lr}
    ldr   r0, =data_0204be08
    ldr   r0, [r0, #4]
    add   r0, #0xc
    bl    func_02023448
    bl    func_02032f5c
    pop   {r3, pc}
}
