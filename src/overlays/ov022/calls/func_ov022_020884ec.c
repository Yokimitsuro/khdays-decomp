extern int data_ov022_020b2e78;
extern int func_01fffde0(int arg0);
void func_ov022_020884ec(int arg0) {
    int s = ((int *)&data_ov022_020b2e78)[1];
    int e = func_01fffde0(arg0);
    if (e == 0) return;
    *(unsigned char *)(s + 0x3c) = (*(unsigned char *)(s + 0x3c) & ~1) | 1;
    *(int *)(e + 0x6c) = 0;
    *(int *)(e + 0x1bc) = 0;
}
