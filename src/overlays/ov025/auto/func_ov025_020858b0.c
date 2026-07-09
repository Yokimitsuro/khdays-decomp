extern int data_ov025_020b574c;
extern int data_ov025_020b4a78;

int func_ov025_020858b0(void) {
    return *(int *)(*(int *)((char *)&data_ov025_020b4a78 + *(int *)((char *)&data_ov025_020b574c + 4) * 8) + 0xc);
}
