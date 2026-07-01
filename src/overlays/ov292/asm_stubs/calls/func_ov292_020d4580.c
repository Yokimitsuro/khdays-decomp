extern void func_ov107_020c9264(void *r0, int r1, int r2);
extern void func_ov292_020d3dfc(void *r0);
extern int func_0203c634(void *r0, int r1, void *r2);
extern void AllocatorFreeForExpHeap_0x020d45bc(void);

asm void func_ov292_020d4580(void *r0)
{
    stmfd   sp!, {r3, r4, r5, lr}
    mov     r5, r0
    ldr     r4, [r5, #4]
    mov     r1, #1
    ldr     r0, [r4]
    mov     r2, r1
    bl      func_ov107_020c9264
    mov     r0, r4
    bl      func_ov292_020d3dfc
    ldrsb   r1, [r5, #0x20]
    ldr     r2, =AllocatorFreeForExpHeap_0x020d45bc
    mov     r0, r5
    bl      func_0203c634
    ldmfd   sp!, {r3, r4, r5, pc}
}
