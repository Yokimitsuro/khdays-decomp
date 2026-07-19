extern void func_ov005_02053250(void);
extern void func_ov005_020536ac(void);
extern void func_ov005_020523f8(int layer);
extern void func_ov005_02054184(void);
extern void func_ov005_020544f4(void);
extern void func_02033b78(int a, int b);
extern unsigned short data_0204c190;
extern char *data_ov005_0205b80c;

/* Per-frame refresh: rebuilds the three layers, and when the pad reports B without A, arms the
 * cancel path. */
void func_ov005_02054774(void) {
    unsigned held;
    func_ov005_02053250();
    func_ov005_020536ac();
    func_ov005_020523f8(1);
    func_ov005_020523f8(0);
    func_ov005_020523f8(3);
    held = data_0204c190;
    if ((held & 1) == 0 && (held & 2) == 0) {
        return;
    }
    *(int *)(data_ov005_0205b80c + 0x4000 + 0xbf0) = 4;
    func_ov005_02054184();
    func_ov005_020544f4();
    func_02033b78(0, 1);
}
