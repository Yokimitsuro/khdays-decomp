extern int PXIi_RequestCmd0x65(int arg0, int arg1, void *cb, int *out);
extern void func_0200cab8(void);
extern void func_0200caf8(int val, int *out);

asm int func_0200ce0c(int arg0, int arg1)
{
    stmdb sp!, {r3, lr}
    ldr r2, =func_0200caf8
    add r3, sp, #0
    bl PXIi_RequestCmd0x65
    cmp r0, #0
    ldmneia sp!, {r3, pc}
    bl func_0200cab8
    ldr r0, [sp]
    ldmia sp!, {r3, pc}
}
