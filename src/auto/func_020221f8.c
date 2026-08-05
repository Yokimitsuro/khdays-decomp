/*
 * Game_ActionSetBranchTarget - action-command handler (opcode table data_020425ec). Sets up a
 * pending script jump for the current action entry. cmd[0] is the branch operand:
 *   - operand != -1: record the current depth (state+0x580 = entries-count at state+0x124) and the
 *     absolute jump target (state+0x584 = the current entry's script pointer at entry+0xc plus the
 *     operand), where entry = state + 4 + count*0x48.
 *   - operand == -1: clear the target (state+0x584 = 0).
 * Either way the pending-jump flag word (state+0x588) is cleared and the handler returns 1.
 *
 * THUMB, reloc-free. Match note: read `operand` before `count` so count is allocated to the
 * callee-saved r5 that survives into the branch (reading count first swaps the roles and lets mwcc
 * tail-merge the two state+0x584 stores). mwcc synthesises the -1 comparand by reusing the 0x48
 * multiplier (sub #0x49).
 */

int func_020221f8(int param_1, int *param_2)
{
    int operand = *param_2;
    int count = *(int *)(param_1 + 0x124);
    int entry = param_1 + 4 + count * 0x48;

    if (operand != -1) {
        *(int *)(param_1 + 0x580) = count;
        *(int *)(param_1 + 0x584) = *(int *)(entry + 0xc) + operand;
    } else {
        *(int *)(param_1 + 0x584) = 0;
    }
    *(int *)(param_1 + 0x588) = 0;
    return 1;
}
