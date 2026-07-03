extern void (*data_ov047_020b42e0[])();
void func_ov047_020b3b98(int param_1, int param_2) {
    int i = 0;
    if ((int)*(unsigned char *)(param_1 + 0x19) <= 0) return;
    {
        int off = 0;
        do {
            int e = *(int *)(param_1 + 0xc) + off;
            int t = *(signed char *)(e + 2);
            if (t != 0) data_ov047_020b42e0[t](param_1, e, param_2);
            i++;
            off += 0x1c8;
        } while (i < (int)*(unsigned char *)(param_1 + 0x19));
    }
}
