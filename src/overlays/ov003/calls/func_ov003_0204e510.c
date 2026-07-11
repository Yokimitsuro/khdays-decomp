extern void MTX_RotY33_(void *buf, int a, int b);
extern void MTX_Concat33(void *dst, void *buf, void *src);
extern short data_0203d210[];
extern int data_ov003_0204f9a0;

void func_ov003_0204e510(int param_1, int param_2) {
    unsigned int buf[9];
    int i = param_2 >> 4;
    int off;
    MTX_RotY33_(buf, data_0203d210[i * 2], data_0203d210[i * 2 + 1]);
    off = param_1 * 0x108;
    MTX_Concat33((void *)(data_ov003_0204f9a0 + 0x290 + off), buf, (void *)(data_ov003_0204f9a0 + 0x290 + off));
    MTX_Concat33((void *)(data_ov003_0204f9a0 + 0xad0 + off), buf, (void *)(data_ov003_0204f9a0 + 0xad0 + off));
    MTX_Concat33((void *)(data_ov003_0204f9a0 + 0xef0 + off), buf, (void *)(data_ov003_0204f9a0 + 0xef0 + off));
}
