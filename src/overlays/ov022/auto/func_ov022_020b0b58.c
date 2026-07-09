int func_ov022_020b0b58(int arg0) {
    int mx = 0;
    int base = *(int *)(*(int *)(arg0 + 0x470) + 0x14);
    int i = 0;
    if (*(short *)(base + 0x30) > 0) {
        int e = *(int *)(base + 0x34);
        do {
            i++;
            if (mx < *(int *)(e + 8)) mx = *(int *)(e + 8);
            e += 0x48;
        } while (i < *(short *)(base + 0x30));
    }
    if (*(unsigned char *)(base + 2) == 2) mx = 0x7fffffff;
    return mx;
}
