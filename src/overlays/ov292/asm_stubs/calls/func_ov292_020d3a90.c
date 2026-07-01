extern void func_0203c7e8(void *r0);
extern void NNSi_FndDestroyDoubleList(void *r0);
extern void func_ov107_020c68ec(void *r0);

asm void func_ov292_020d3a90(void *r0)
{
    stmfd   sp!, {r4, lr}
    mov     r4, r0
    ldr     r0, [r4, #0x384]
    bl      func_0203c7e8
    add     r0, r4, #0x394
    bl      NNSi_FndDestroyDoubleList
    mov     r0, r4
    bl      func_ov107_020c68ec
    ldmfd   sp!, {r4, pc}
}
