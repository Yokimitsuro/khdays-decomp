extern int SND_CountReservedCommand(void);
extern int func_02008aa0(void);

asm int SND_CountWaitingCommand(void)
{
    stmdb sp!, {r4, lr}
    bl SND_CountReservedCommand
    mov r4, r0
    bl func_02008aa0
    rsb r1, r4, #0x100
    sub r0, r1, r0
    ldmia sp!, {r4, pc}
}
