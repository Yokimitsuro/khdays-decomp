extern int PXIi_TryLock(void);
extern void PXIi_SendCommand(unsigned int cmd);

struct CC { char _0[0x20]; int field_20; int field_24; };
extern struct CC data_020463cc;
extern short data_02046410[];
extern int data_02046414[];

asm int PXIi_RequestCmd0x65(int arg0, int arg1, int arg2, int arg3)
{
    stmdb sp!, {r3, r4, r5, r6, r7, lr}
    mov r5, r0
    mov r4, r1
    mov r7, r2
    mov r6, r3
    bl  PXIi_TryLock
    cmp r0, #0
    moveq r0, #1
    ldmeqia sp!, {r3, r4, r5, r6, r7, pc}
    ldr r1, =data_020463cc
    and r0, r5, #0xff
    str r7, [r1, #0x20]
    orr r0, r0, #0x6500
    ldr r2, =data_02046410
    str r6, [r1, #0x24]
    mov r3, r5, lsl #3
    mov ip, #0
    ldr r1, =data_02046414
    strh ip, [r2, r3]
    orr r0, r0, #0x3000000
    str r4, [r1, r5, lsl #3]
    bl  PXIi_SendCommand
    mov r0, #0
    ldmia sp!, {r3, r4, r5, r6, r7, pc}
}
