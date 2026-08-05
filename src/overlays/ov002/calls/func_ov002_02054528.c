/*
 * func_ov002_02054528 - allocate and initialise a record from a template (ARM).
 *
 * Allocates a new record via func_ov002_02053f4c(param_1), then fills it: the type word (+0) from
 * param_3, seven template fields copied from param_2 (+2/+4/+0xa/+0xc signed, +6/+8 unsigned
 * halfwords, +0x18 word), the payload pointer (+0x10) from param_4, and the active flag (+0x14) set
 * to 1.
 */
extern int func_ov002_02053f4c(int a);

void func_ov002_02054528(int param_1, int param_2, int param_3, int param_4)
{
    int obj = func_ov002_02053f4c(param_1);
    *(short *)(obj + 0) = param_3;
    *(short *)(obj + 2) = *(short *)(param_2 + 2);
    *(short *)(obj + 4) = *(short *)(param_2 + 4);
    *(unsigned short *)(obj + 6) = *(unsigned short *)(param_2 + 6);
    *(unsigned short *)(obj + 8) = *(unsigned short *)(param_2 + 8);
    *(short *)(obj + 0xa) = *(short *)(param_2 + 0xa);
    *(short *)(obj + 0xc) = *(short *)(param_2 + 0xc);
    *(int *)(obj + 0x10) = param_4;
    *(int *)(obj + 0x18) = *(int *)(param_2 + 0x18);
    *(int *)(obj + 0x14) = 1;
}
