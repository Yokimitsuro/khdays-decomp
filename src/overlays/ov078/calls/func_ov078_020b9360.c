extern void (*data_ov078_020ba448[])();
void func_ov078_020b9360(int param_1, int param_2) {
    int i = 0;
    if ((int)*(unsigned char *)(param_1 + 0x19) <= 0) return;
    {
        int off = 0;
        do {
            int e = *(int *)(param_1 + 0xc) + off;
            int t = *(signed char *)(e + 2);
            if (t != 0) data_ov078_020ba448[t](param_1, e, param_2);
            i++;
            off += 0x1c8;
        } while (i < (int)*(unsigned char *)(param_1 + 0x19));
    }
}
