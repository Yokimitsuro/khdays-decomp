/*
 * func_ov002_020766e0 - record a hit against an array element and test its result (ARM).
 *
 * Copies the tag byte param_1[0x11] into param_2[1], derives param_1's index within its owning array
 * (byte offset from the array base at param_1[8]+0x54 divided by the element size at param_1[8]+0x4e,
 * via func_02020400) and stores it into param_2[2]. Then submits the record with tag 5 through
 * func_02031384, returning 1 when the returned id is a real value (not the 0xffff sentinel), 0 otherwise.
 */
extern int func_02020400(int a, int b);
extern int func_02031384(int a, int b, int c);

int func_ov002_020766e0(int param_1, int param_2, int param_3)
{
    int base;
    *(unsigned char *)(param_2 + 1) = *(unsigned char *)(param_1 + 0x11);
    base = *(int *)(param_1 + 8);
    *(unsigned short *)(param_2 + 2) =
        func_02020400(param_1 - *(int *)(base + 0x54), *(unsigned short *)(base + 0x4e));
    return func_02031384(5, param_2, (unsigned short)param_3) != 0xffff;
}
