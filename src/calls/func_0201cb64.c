extern void SNDi_FreeVoiceChannel(void *);

asm void func_0201cb64(void *object)
{
    stmdb sp!, {r3, lr}
    ldr r2, [r0]
    cmp r2, #0
    ldmeqia sp!, {r3, pc}
    ldr r0, [r0]
    bl SNDi_FreeVoiceChannel
    ldmia sp!, {r3, pc}
}
