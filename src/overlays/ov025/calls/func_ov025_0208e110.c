typedef unsigned short u16;
extern void func_0202accc(int obj, unsigned int trackId, int animBlock, int param_2);
extern const u16 data_ov025_020b3ba4[];

void func_ov025_0208e110(int param_1, int param_2) {
    u16 tracks[6];
    u16 *p = tracks;
    unsigned int i;
    p[0] = data_ov025_020b3ba4[0];
    p[1] = data_ov025_020b3ba4[1];
    p[2] = data_ov025_020b3ba4[2];
    p[3] = data_ov025_020b3ba4[3];
    p[4] = data_ov025_020b3ba4[4];
    i = 0;
    do {
        func_0202accc(param_1, p[i], param_1 + 0xe0, param_2);
        i++;
    } while (i < 5);
}
