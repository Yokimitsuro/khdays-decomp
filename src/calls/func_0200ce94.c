extern int PXIi_SendCmd0x64(int arg0, int arg1, void *cb, int *out);
extern void func_0200cab8(void);
extern void func_0200caf8(int val, int *out);

asm int func_0200ce94(int arg0, int arg1)
{
    stmdb sp!, {r3, lr}
    ldr r2, =func_0200caf8
    add r3, sp, #0
    bl PXIi_SendCmd0x64
    cmp r0, #0
    ldmneia sp!, {r3, pc}
    bl func_0200cab8
    ldr r0, [sp]
    ldmia sp!, {r3, pc}
}
