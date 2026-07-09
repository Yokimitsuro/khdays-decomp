extern int func_ov022_02083c08(int arg0);
extern int func_ov022_02083758(void);
extern int *data_ov022_020b2e60;
int func_ov022_02083714(void) {
    int *base;
    func_ov022_02083c08(0);
    base = data_ov022_020b2e60;
    if (base[1] > 2) {
        base[1] = 0;
        return (int)&func_ov022_02083758;
    }
    base[1]++;
    return 0;
}
