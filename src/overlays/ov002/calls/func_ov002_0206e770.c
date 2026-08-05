/*
 * func_ov002_0206e770 - test whether the mission-clear sequence is in a "finished" state (ARM).
 *
 * With param_1 == 0 it inspects the result-screen phase (the halfword at base+0x8ba8, offset by
 * -10000 to a small enum): the sequence counts as finished only while that phase is 0 or 1. With
 * param_1 != 0 it instead checks the flow state word at base+0x8b58 for the completed value 7 (and
 * treats a null base as not finished). base = *(int*)&data_ov002_0207fa00. Both failure paths share
 * a single `return 0` so mwcc branches to one tail as the ROM does.
 */
extern int data_ov002_0207fa00;

int func_ov002_0206e770(int param_1)
{
    int base = *(int *)&data_ov002_0207fa00;
    if (param_1 == 0) {
        short s = *(short *)(base + 0x8ba8) - 10000;
        if ((unsigned short)s > 1) goto ret0;
        return 1;
    }
    if (base == 0) goto ret0;
    return *(int *)(base + 0x8b58) == 7;
ret0:
    return 0;
}
