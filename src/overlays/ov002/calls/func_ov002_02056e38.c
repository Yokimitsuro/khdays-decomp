/* Set the panel's mode halfword at +0x1a4: 7 when func_ov002_0205e2b8 accepts
 * the request, otherwise whatever func_ov002_0205da24 resolves it to. */
extern int func_ov002_0205e2b8(int req);
extern void func_ov002_0205e2c4(int req);
extern int func_ov002_0205da24(int req);

extern char *data_ov002_0207f614;

void func_ov002_02056e38(int req) {
    char *ctx = data_ov002_0207f614;

    if (func_ov002_0205e2b8(req) != 0) {
        func_ov002_0205e2c4(req);
        *(short *)(ctx + 0x1a4) = 7;
    } else {
        *(short *)(ctx + 0x1a4) = (short)func_ov002_0205da24(req);
    }
}
