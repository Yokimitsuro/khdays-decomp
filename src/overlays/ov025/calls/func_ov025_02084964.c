extern int func_ov025_02083a9c();
extern int data_ov025_020b5744;

void func_ov025_02084964(int arg0) {
    int r = func_ov025_02083a9c(arg0);
    if (r == -1) {
        return;
    }
    *(unsigned char *)(*(int *)((char *)&data_ov025_020b5744 + 4) + 0x963c) |= 1 << r;
}
