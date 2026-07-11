/* Resolve a byte-code operand's absolute value: decode the current instruction
 * (func_020218a4) for slot param_1's context block (at param_1+4+ctx*0x48, ctx =
 * *(param_1+0x124)). Opcode 0x40 indexes a runtime table (base +0x14) by the operand
 * plus a global selector (func_02024e5c)*4; any other opcode is a plain base+operand. */
#pragma thumb on
extern short *func_020218a4(int a, unsigned short *b);
extern int func_02024e5c(void);
int func_02021948(int param_1, unsigned short *param_2) {
    int iVar5 = param_1 + 4 + *(int *)(param_1 + 0x124) * 0x48;
    short *puVar1 = func_020218a4(param_1, param_2);
    if (*puVar1 == 0x40) {
        int base = *(int *)(iVar5 + 0x14) + *(volatile int *)(puVar1 + 2);
        int iVar3 = func_02024e5c();
        return *(int *)(iVar5 + 0x14) + *(int *)(base + iVar3 * 4);
    }
    return *(int *)(iVar5 + 0x14) + *(volatile int *)(puVar1 + 2);
}
