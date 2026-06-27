/* Vtable/state-swap helper (NOT OS_DisableIrq — does not touch CPSR). Caller func_0203c8b0
 * passes 0 or 1 to choose between two pairs of function pointers, writing both to a global
 * dispatcher at &data_0204bbfc+0xc and +0x10. Equivalent to a 2-state "set callbacks" toggle.
 *   flag=1: g->cb_c = func_0201e9e4; g->cb_10 = func_0201ea28;
 *   flag=0: g->cb_c = func_0201e9fc; g->cb_10 = func_0201ea40;
 */
extern void func_0201e9e4(void);
extern void func_0201e9fc(void);
extern void func_0201ea28(void);
extern void func_0201ea40(void);
extern void *data_0204bbfc[];

asm void func_0201f390(int on)
{
    cmp    r0, #0
    ldrne  r2, =func_0201e9e4
    ldrne  r0, =data_0204bbfc
    ldrne  r1, =func_0201ea28
    strne  r2, [r0, #0xc]
    strne  r1, [r0, #0x10]
    bxne   lr
    ldr    r2, =func_0201e9fc
    ldr    r0, =data_0204bbfc
    ldr    r1, =func_0201ea40
    str    r2, [r0, #0xc]
    str    r1, [r0, #0x10]
    bx     lr
}
