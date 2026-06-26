extern int func_02030788();
extern int func_ov022_020a35f4();

int func_ov038_020b472c(int *r0)
{
    int *r4 = r0;

    if (func_02030788() == 0) {
        *(long long *)((char *)r4 + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(long long *)((char *)r4 + 0x46c) |= 0x10000;
    }
    return func_ov022_020a35f4(r4, 0x21);
}
