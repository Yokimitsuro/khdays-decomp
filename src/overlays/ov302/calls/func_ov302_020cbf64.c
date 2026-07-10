extern void *NNSi_FndAllocFromDefaultExpHeap(int size);
extern void MI_CpuFill8(void *dst, int val, int n);
extern void *func_ov302_020cbf20(void *out, void *cur);

/* Allocate and populate a 0x58-byte runtime record from the packed source
 * template at `param_1`, then link four sub-lists parsed sequentially out of
 * `param_2` via func_ov302_020cbf20. Returns the new record. */
void *func_ov302_020cbf64(int param_1, void *param_2) {
    unsigned int *p = (unsigned int *)NNSi_FndAllocFromDefaultExpHeap(0x58);
    char *cp = (char *)p;
    void *local;

    MI_CpuFill8(p, 0, 0x58);
    *(unsigned short *)(cp + 0) = *(unsigned short *)(param_1 + 2);
    *(unsigned short *)(cp + 2) = *(unsigned short *)(param_1 + 4);
    *(unsigned short *)(cp + 4) = *(unsigned short *)(param_1 + 0xa);
    *(unsigned short *)(cp + 6) = *(unsigned short *)(param_1 + 0xe);
    *(unsigned short *)(cp + 8) = *(unsigned short *)(param_1 + 0x10);
    *(unsigned short *)(cp + 0xa) = *(unsigned short *)(param_1 + 0x12);
    *(unsigned char *)(cp + 0xc) = *(unsigned char *)(param_1 + 0x14);
    p[4] = (*(unsigned short *)(param_1 + 0xc) == 1);
    *(unsigned char *)(cp + 0x14) = *(unsigned char *)(param_1 + 0x16);
    *(unsigned char *)(cp + 0xd) = *(unsigned char *)(param_1 + 0x15);
    *(unsigned char *)(cp + 0x15) = *(unsigned char *)(param_1 + 0x17);
    p[7] = *(unsigned short *)(param_1 + 6);
    p[6] = *(unsigned char *)(param_1 + 0x23);
    *(unsigned short *)(cp + 0x20) = *(unsigned short *)(param_1 + 0x18);
    *(unsigned short *)(cp + 0x22) = *(unsigned short *)(param_1 + 0x1a);
    *(unsigned short *)(cp + 0x24) = *(unsigned short *)(param_1 + 0x1c);
    *(char *)(cp + 0x26) = (char)*(unsigned short *)(param_1 + 0x1e);
    *(char *)(cp + 0x27) = (char)*(unsigned short *)(param_1 + 0x20);
    *(unsigned char *)(cp + 0x28) = *(unsigned char *)(param_1 + 0x22);
    *(unsigned short *)(cp + 0x2a) = *(unsigned short *)(param_1 + 0x24);
    *(unsigned short *)(cp + 0x2c) = *(unsigned short *)(param_1 + 0x26);
    *(unsigned short *)(cp + 0x2e) = *(unsigned short *)(param_1 + 0x28);
    p[0xc] = *(unsigned short *)(param_1 + 0x2a);
    p[0xd] = *(unsigned short *)(param_1 + 0x2c);
    p[0xe] = *(unsigned short *)(param_1 + 0x2e);
    p[0xf] = (unsigned int)func_ov302_020cbf20(&local, param_2);
    p[0x10] = (unsigned int)func_ov302_020cbf20(&local, local);
    p[0x11] = (unsigned int)func_ov302_020cbf20(&local, local);
    p[0x12] = (unsigned int)func_ov302_020cbf20(0, local);
    return p;
}
