extern int func_0203c650();
extern int func_ov107_020c7ca4();

int func_ov224_020d05c4(int r0)
{
    signed char c = *(signed char *)(r0 + 0x1c6);
    if (!((c == 9 || c == 0x48) && (*(unsigned char *)(r0 + 0x1c4) & 0xa) == 0)) {
        int a = *(int *)(r0 + 0x440);
        if (a) {
            func_0203c650(*(int *)(r0 + 0x3c), a);
            *(int *)(r0 + 0x440) = 0;
        }
        a = *(int *)(r0 + 0x448);
        if (a) {
            func_0203c650(*(int *)(r0 + 0x3c), a);
            *(int *)(r0 + 0x448) = 0;
        }
    }
    return func_ov107_020c7ca4(r0);
}
