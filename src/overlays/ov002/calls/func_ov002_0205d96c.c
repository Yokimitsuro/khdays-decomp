extern void func_ov002_0205d214(int id, unsigned int arg);
extern void func_ov002_0205bff4(unsigned int kind, int flag);
extern char *data_ov002_0207f620;
/* HUD reset: run the two sub-updaters (id 0 with arg, and kind = ctx's first byte with flag 0),
 * then clear the ctx word at +0x10. */
void func_ov002_0205d96c(unsigned int arg) {
    int ctx = (int)data_ov002_0207f620;
    func_ov002_0205d214(0, arg);
    func_ov002_0205bff4(*(unsigned char *)ctx, 0);
    *(int *)(ctx + 0x10) = 0;
}
