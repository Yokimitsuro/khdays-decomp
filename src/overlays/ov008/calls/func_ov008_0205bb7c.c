typedef unsigned short u16;
extern void func_0202accc(int obj, unsigned int trackId, int animBlock, int param_2);
extern const u16 data_ov008_0208f044[];

void func_ov008_0205bb7c(int param_1, int param_2) {
    u16 tracks[6];
    u16 *p = tracks;
    unsigned int i;
    p[0] = data_ov008_0208f044[0];
    p[1] = data_ov008_0208f044[1];
    p[2] = data_ov008_0208f044[2];
    p[3] = data_ov008_0208f044[3];
    p[4] = data_ov008_0208f044[4];
    i = 0;
    do {
        func_0202accc(param_1, p[i], param_1 + 0xe0, param_2);
        i++;
    } while (i < 5);
}
