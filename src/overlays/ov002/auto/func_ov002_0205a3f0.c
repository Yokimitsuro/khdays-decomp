/*
 * func_ov002_0205a3f0 - classify an input code into a category, with an optional remainder out-param
 * (ARM, reloc-free, jump table).
 *
 * param_2 (0..10) selects a category 0..5; when param_1 is non-null it also receives the offset of
 * param_2 within its category's range:
 *   0            -> category 0, remainder 0
 *   1,2,3        -> category 1, remainder param_2-1
 *   4,5          -> category 2, remainder param_2-4
 *   6,7,8        -> category 3, remainder param_2-6
 *   10           -> category 5, remainder 0
 *   9            -> category 4, remainder 0
 * Out-of-range param_2 falls through and returns param_1 unchanged.
 *
 * Cases 10 and 9 are written in that order because the jump-table block layout places case 10's body
 * before case 9's (mwcc emits case bodies in source order).
 */
int func_ov002_0205a3f0(int param_1, int param_2)
{
    switch (param_2) {
    case 0:
        if (param_1) *(int *)param_1 = 0;
        return 0;
    case 1: case 2: case 3:
        if (param_1) *(int *)param_1 = param_2 - 1;
        return 1;
    case 4: case 5:
        if (param_1) *(int *)param_1 = param_2 - 4;
        return 2;
    case 6: case 7: case 8:
        if (param_1) *(int *)param_1 = param_2 - 6;
        return 3;
    case 10:
        if (param_1) *(int *)param_1 = 0;
        return 5;
    case 9:
        if (param_1) *(int *)param_1 = 0;
        return 4;
    }
    return param_1;
}
