extern int func_0203c5c0(int owner, int a, int b, void *step, void *done, int **out);
extern void func_ov284_020cd2fc(void);
extern void func_ov284_020cd508(char *obj);

int func_ov284_020cd294(int obj) {
    int *out;
    int r = func_0203c5c0(*(int *)(obj + 0x3c), 0x64, 8, (void *)func_ov284_020cd2fc,
                          (void *)func_ov284_020cd508, &out);
    out[0] = obj;
    out[1] = *(int *)(obj + 0x3ac);
    *(int *)(out[1] + 0x5c) &= ~2;
    return r;
}
