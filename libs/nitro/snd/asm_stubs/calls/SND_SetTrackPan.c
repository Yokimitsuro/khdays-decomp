extern void SNDi_SetTrackParam(void);

asm void SND_SetTrackPan(void)
{
    stmdb sp!, {r3, lr}
    mov r3, r2
    mov ip, #1
    mov r2, #9
    str ip, [sp]
    bl SNDi_SetTrackParam
    ldmia sp!, {r3, pc}
}
