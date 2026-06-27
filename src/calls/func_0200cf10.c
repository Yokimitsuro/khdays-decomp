extern int func_0200cebc(int arg0, void *cb, int *out);
extern void func_0200cab8(void);
extern void func_0200caf8(int val, int *out);

asm int func_0200cf10(int arg0)
{
    stmdb sp!, {r3, lr}
    ldr r1, =func_0200caf8
    add r2, sp, #0
    bl func_0200cebc
    cmp r0, #0
    ldmneia sp!, {r3, pc}
    bl func_0200cab8
    ldr r0, [sp]
    ldmia sp!, {r3, pc}
}
