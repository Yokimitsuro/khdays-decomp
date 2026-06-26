extern int *func_02010128();

int *func_ov004_0204d2ec(char *param)
{
    int *p;

    p = func_02010128(param + 0x18);
    if (p != 0) {
        while (p[4] != 0) {
            p = func_02010128(param + 0x18);
            if (p == 0)
                break;
        }
    }
    return p;
}
