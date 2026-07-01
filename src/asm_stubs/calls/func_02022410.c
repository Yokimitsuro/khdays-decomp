/* Set-and-commit helper:
 *   if (func_02033cc8(arg0, arg1) != 0) return 0;
 *   data_020425e8 = (u8)arg1;
 *   func_020335ec((u8)arg1);
 *   return 1;
 */
extern int  func_02033cc8(int a, int b);
extern void func_020335ec(int v);
extern unsigned char data_020425e8;

asm int func_02022410(int a, int b)
{
    push  {r4, lr}
    add   r4, r1, #0
    bl    func_02033cc8
    cmp   r0, #0
    bne   fail
    ldr   r0, =data_020425e8
    strb  r4, [r0]
    lsl   r0, r4, #0x18
    lsr   r0, r0, #0x18
    bl    func_020335ec
    mov   r0, #1
    pop   {r4, pc}
fail:
    mov   r0, #0
    pop   {r4, pc}
}
