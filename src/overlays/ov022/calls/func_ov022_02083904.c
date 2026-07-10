extern void func_ov022_02083c08(int a);
extern int func_0201e428(void);
extern int func_0201e438(void);
extern int func_ov002_0205196c(void);
extern void func_ov002_0205193c(void);
extern void func_ov002_02051994(void);
extern void func_ov022_0208398c(void);
extern int data_ov022_020b2e60;

int func_ov022_02083904(void) {
    int v;
    func_ov022_02083c08(1);
    v = *(signed char *)(data_ov022_020b2e60 + 0x3e);
    if (v != 0) {
        if (v == 2) {
            if (func_ov002_0205196c() == 0) return 0;
            func_ov002_0205193c();
        }
    } else {
        *(int *)(data_ov022_020b2e60 + 0x1c) = func_0201e428() << 0xc;
        *(int *)(data_ov022_020b2e60 + 0x20) = func_0201e438() << 0xc;
        if (func_ov002_0205196c() == 0) func_ov002_02051994();
    }
    return (int)func_ov022_0208398c;
}
