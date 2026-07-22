/* Release every tile surface the page owns: the two fixed ones at +0x34 and
 * +0x70, then the variable-length run starting at +0xac -- four entries when the
 * object at +0x30 is present, otherwise two. All of them are 0x3c apart, which
 * is the TileSurface stride, so the three offsets are one contiguous array. */
extern void func_0202ffbc(void *surface);

extern char *data_ov002_0207f9fc;

void func_ov002_020676c8(void) {
    char *ctx = data_ov002_0207f9fc;
    int count = *(int *)(ctx + 0x30) != 0 ? 4 : 2;
    int i;

    func_0202ffbc(ctx + 0x34);
    func_0202ffbc(ctx + 0x70);

    i = 0;
    if (count > 0) {
        ctx += 0xac;
        do {
            func_0202ffbc(ctx);
            ctx += 0x3c;
            i++;
        } while (i < count);
    }
}
