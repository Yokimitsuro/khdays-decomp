extern int func_020325a0(int r0, int r1);

int func_ov005_0204e15c(int r0, int *r1)
{
    int i;
    int result;

    result = -1;
    for (i = 0; i < 2; i++) {
        int v = r1[i + 5];
        if (v != -1) {
            result = v;
            break;
        }
    }
    return func_020325a0(r0, result);
}
