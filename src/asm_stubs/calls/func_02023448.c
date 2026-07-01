extern int  func_02020a9c(void *p);
extern void GFXi_EnqueueCommand(int cmd, int n, void *src, void *cb);

asm void func_02023448(void *self)
{
    push {r4, lr}
    add  r4, r0, #0
    bl   func_02020a9c
    mov  r1, #2
    tst  r0, r1
    bne  hot
    mov  r0, #0xb
    b    join
hot:
    mov  r0, #0xa
join:
    add  r4, #0x94
    ldr  r3, [r4, #0]
    mov  r1, #0
    add  r2, r3, #0
    ldr  r3, [r3, #8]
    add  r2, #0xc
    bl   GFXi_EnqueueCommand
    pop  {r4, pc}
}
