extern int func_ov025_02083a9c();
extern int data_ov025_020b5744;

void func_ov025_0208499c(int arg0) {
    unsigned int idx = func_ov025_02083a9c(arg0);
    if (idx == 0xffffffff) return;
    *(unsigned char *)(*(int *)((char *)&data_ov025_020b5744 + 4) + 0x963c) &= ~(1 << idx);
}
