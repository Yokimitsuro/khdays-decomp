/* func_020223dc (THUMB): r4=func_02021980(r5,r1); if (func_02033cc8())
 *   call func_020219b4(r5,r4), return 0;
 * else *data_020425e8 = r4 (byte), then func_020335ec((u8)r4); return 1.
 */
extern void *func_02021980(void *a, void *b);
extern int  func_02033cc8(void);
extern void func_020219b4(void *a, void *b);
extern int  func_020335ec(int b);
extern char data_020425e8;

asm int func_020223dc(void *a, void *b)
{
    push  {r3, r4, r5, lr}
    add   r5, r0, #0
    bl    func_02021980
    add   r4, r0, #0
    bl    func_02033cc8
    cmp   r0, #0
    beq   notify
    add   r0, r5, #0
    add   r1, r4, #0
    bl    func_020219b4
    mov   r0, #0
    pop   {r3, r4, r5, pc}
notify:
    ldr   r0, =data_020425e8
    strb  r4, [r0]
    lsl   r0, r4, #0x18
    lsr   r0, r0, #0x18
    bl    func_020335ec
    mov   r0, #1
    pop   {r3, r4, r5, pc}
}
