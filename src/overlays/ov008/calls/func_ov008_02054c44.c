extern void func_020326a8(int arg0, int arg1);

void func_ov008_02054c44(int arg0, void *object)
{
    int i;

    for (i = 0; i < 2; i++) {
        int value = ((int *)object)[i + 5];

        if (value != -1) {
            func_020326a8(arg0, value);
        }
    }
}
