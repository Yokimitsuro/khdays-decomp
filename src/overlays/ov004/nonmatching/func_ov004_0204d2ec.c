extern int *NNS_FndGetNextListObject();

int *func_ov004_0204d2ec(char *param)
{
    int *p;

    p = NNS_FndGetNextListObject(param + 0x18);
    if (p != 0) {
        while (p[4] != 0) {
            p = NNS_FndGetNextListObject(param + 0x18);
            if (p == 0)
                break;
        }
    }
    return p;
}
