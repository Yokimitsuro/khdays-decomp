extern void *SND_GetWaveDataAddress(void *player, int wave);
extern int SND_GetWaveDataCount(void *player);
extern void SND_SetWaveDataAddress(void *player, int wave, void *addr);
extern void DC_StoreRange(void *addr, unsigned int size);
extern void *func_0201b9a0(void *heap, unsigned int size, void *cb, void *obj, int wave);
extern int func_0201b6f4(void *src, void *dst, unsigned int size, int offset);
extern void func_0201c354(void *addr, int size, void *player, int wave);

asm int func_0201c39c(void *obj, int wave, void *src, void *heap)
{
    stmdb sp!, {r3, r4, r5, r6, r7, r8, sb, lr}
    mov r8, r0
    mov r7, r1
    mov r6, r2
    mov r5, r3
    bl SND_GetWaveDataAddress
    cmp r0, #0
    movne r0, #1
    ldmneia sp!, {r3, r4, r5, r6, r7, r8, sb, pc}
    mov r0, r8
    bl SND_GetWaveDataCount
    ldr r1, [r8, #0x38]
    sub r0, r0, #1
    add r1, r1, r7
    add r1, r8, r1, lsl #2
    cmp r7, r0
    ldrlo r0, [r1, #0x40]
    ldr r4, [r1, #0x3c]
    ldrhs r0, [r8, #8]
    cmp r5, #0
    sub sb, r0, r4
    moveq r0, #0
    ldmeqia sp!, {r3, r4, r5, r6, r7, r8, sb, pc}
    ldr r2, =func_0201c354
    mov r0, r5
    mov r3, r8
    add r1, sb, #0x20
    str r7, [sp]
    bl func_0201b9a0
    movs r5, r0
    moveq r0, #0
    ldmeqia sp!, {r3, r4, r5, r6, r7, r8, sb, pc}
    mov r0, r6
    mov r1, r5
    mov r2, sb
    mov r3, r4
    bl func_0201b6f4
    cmp sb, r0
    movne r0, #0
    ldmneia sp!, {r3, r4, r5, r6, r7, r8, sb, pc}
    mov r0, r5
    mov r1, sb
    bl DC_StoreRange
    mov r0, r8
    mov r1, r7
    mov r2, r5
    bl SND_SetWaveDataAddress
    mov r0, #1
    ldmia sp!, {r3, r4, r5, r6, r7, r8, sb, pc}
}
