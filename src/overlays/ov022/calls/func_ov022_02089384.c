extern void func_01fff774(unsigned short *arg0, unsigned int idx, int arg2);

struct tbl5_02089384 {
    unsigned int v[5];
};
extern struct tbl5_02089384 data_ov022_020b2380;

void func_ov022_02089384(unsigned short *param_1, int param_2) {
    struct tbl5_02089384 tbl = data_ov022_020b2380;
    int i = 0;
    do {
        if ((short)param_1[(tbl.v[i] & 0xffff) + 0x70] > 0) {
            func_01fff774(param_1, tbl.v[i] & 0xffff, param_2);
        }
        i = i + 1;
    } while (i < 5);
}
