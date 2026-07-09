extern int func_ov025_0209bf40();
extern int data_ov025_020b4ed0;

int func_ov025_0209bf74(int arg0, int arg1) {
    int base = func_ov025_0209bf40(arg0);
    if (arg1 >= *(unsigned char *)(base + 2)) {
        return 0;
    }
    return (int)((char *)&data_ov025_020b4ed0 + *(unsigned char *)(base + arg1 + 3) * 4);
}
