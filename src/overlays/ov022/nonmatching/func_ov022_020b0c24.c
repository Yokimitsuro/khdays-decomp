/*
 * [nonmatching: final-block register-coloring: the *(arg3)+0x1000 fixed-point scale computes +0x1000 into a fresh reg (keeping the value in r1 for the product) in the original; mwcc adds in place. First 4 of 5 scale blocks match exactly]
 *
 * Equivalent C; mwcc 3.0/139 diverges only in the noted codegen. Left uncarved.
 */
void func_ov022_020b0c24(int arg0, unsigned int *arg1, unsigned int *arg2, int *arg3, int arg4) {
    int scale = (short)arg4;
    long long v;
    if (scale <= 0x400) scale = 0x1000;
    if ((*(unsigned char *)(arg0 + 0x13) & 1) != 0) {
        v = (long long)(int)arg1[0] * scale + 0x800;
        arg1[0] = (unsigned int)((unsigned long long)v >> 0xc);
    }
    if ((*(unsigned char *)(arg0 + 0x13) & 2) != 0) {
        v = (long long)(int)arg1[1] * scale + 0x800;
        arg1[1] = (unsigned int)((unsigned long long)v >> 0xc);
    }
    if ((*(unsigned char *)(arg0 + 0x13) & 4) != 0) {
        v = (long long)(int)arg1[2] * scale + 0x800;
        arg1[2] = (unsigned int)((unsigned long long)v >> 0xc);
    }
    if ((*(unsigned char *)(arg0 + 0x13) & 8) != 0) {
        v = (long long)(int)arg2[0] * scale + 0x800;
        arg2[0] = (unsigned int)((unsigned long long)v >> 0xc);
    }
    if ((*(unsigned char *)(arg0 + 0x13) & 0x10) == 0) return;
    {
        int cur = *arg3;
        v = (long long)(cur + 0x1000) * scale + 0x800;
    }
    scale = (int)(unsigned int)((unsigned long long)v >> 0xc) - 0x1000;
    if (scale < -0x1000) scale = -0x1000;
    if (0x1000 < scale) scale = 0x1000;
    *arg3 = scale;
}
