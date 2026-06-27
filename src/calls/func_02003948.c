extern void OS_Terminate(void);
extern unsigned short OS_GetLockID(void);
extern void CARD_LockRom(unsigned short lockId);
extern void MI_StopDma(int channel);
extern void OS_SetIrqMask(unsigned int mask);
extern void OS_ResetRequestIrqMask(unsigned int mask);
extern void OSi_SendToPxi(unsigned int data);
extern void func_01ff82fc(void);

asm void func_02003948(int arg0)
{
    stmdb sp!, {r4, lr}
    ldr r1, =0x027ffc40
    mov r4, r0
    ldrh r0, [r1]
    cmp r0, #2
    moveq r0, #1
    movne r0, #0
    cmp r0, #0
    beq _skip
    bl OS_Terminate
_skip:
    bl OS_GetLockID
    mov r0, r0, lsl #0x10
    mov r0, r0, lsr #0x10
    bl CARD_LockRom
    ldr r0, =0
    bl MI_StopDma
    ldr r0, =1
    bl MI_StopDma
    ldr r0, =2
    bl MI_StopDma
    ldr r0, =3
    bl MI_StopDma
    ldr r0, =0x00040000
    bl OS_SetIrqMask
    ldr r0, =0xffffffff
    bl OS_ResetRequestIrqMask
    ldr r1, =0x027ffc20
    ldr r0, =0x10
    str r4, [r1]
    bl OSi_SendToPxi
    ldr r0, =0x027e3f80
    ldr r1, =0x800
    sub r0, r0, r1
    mov sp, r0
    bl func_01ff82fc
    ldmia sp!, {r4, pc}
}
