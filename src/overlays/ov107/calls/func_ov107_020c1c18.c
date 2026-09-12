extern void func_0203d194(void *p);
extern void func_ov107_020cb570(int *p, int v);

void func_ov107_020c1c18(char *self, void *pAnim, int duration) {
    if (*(void **)(self + 0xf4) != 0) {
        func_0203d194(*(void **)(self + 0xf4));
        *(void **)(self + 0xf4) = 0;
    }
    if (pAnim != 0) {
        *(void **)(self + 0xf4) = pAnim;
        func_ov107_020cb570((int *)pAnim, (int)self);
        if (duration > 0) {
            *(int *)(self + 0xf8) = duration;
            *(unsigned short *)(self + 0x48) &= ~1;
        } else {
            *(int *)(self + 0xf8) = 0;
            *(unsigned short *)(self + 0x48) |= 1;
        }
    }
}
