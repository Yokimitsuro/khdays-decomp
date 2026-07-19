extern char *data_ov026_02091368;
extern void func_0201e374(int value);
extern void func_0201e3cc(int value);
extern void func_ov026_02085aa4(void);
extern void func_ov026_0208a774(void);
extern void func_ov026_0208acc4(void);

/* Fade-in tick for the selection screen: 12 frames of brightness ramp (4x faster when the fast
 * flag is set), then hands over to the idle state. */
void *func_ov026_0208ac00(void) {
    void *next = 0;
    char *st = *(char **)&data_ov026_02091368;
    int v = *(int *)st;
    if (v < 0xc) {
        if (*(int *)(st + 0xc3d8) != 0) {
            *(int *)st = v + 4;
        } else {
            *(int *)st = v + 1;
            func_0201e374((v + 1) * 16 / 12 - 0x10);
        }
        func_0201e3cc(*(int *)st * 16 / 12 - 0x10);
    } else {
        next = (void *)&func_ov026_0208acc4;
    }
    func_ov026_02085aa4();
    func_ov026_0208a774();
    return next;
}
