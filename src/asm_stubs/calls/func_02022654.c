extern void func_0201ef58(void);
extern void func_0201f5ac(int arg);

asm void func_02022654(int arg0, int arg1)
{
    push {r4, lr}
    add r4, r0, #0
    cmp r1, #0
    blt _end
    bl  func_0201ef58
    mov r0, #0x4a
    lsl r0, r0, #2
    ldr r0, [r4, r0]
    ldr r0, [r0, #0x28]
    bl  func_0201f5ac
_end:
    pop  {r4, pc}
}
