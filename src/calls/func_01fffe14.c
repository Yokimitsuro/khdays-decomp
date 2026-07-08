extern int func_02030788();
extern int data_ov022_020b2e78[];
extern unsigned char data_0204be04;
int func_01fffe14(void)
{
    unsigned int *p = *(unsigned int **)((char *)data_ov022_020b2e78 + 4);
    if (p == 0)
        return 0;
    if ((*p & 2) == 0) {
        if (data_0204be04 != 0 && p[4] != 0)
            return 1;
        return 0;
    }
    return func_02030788();
}
