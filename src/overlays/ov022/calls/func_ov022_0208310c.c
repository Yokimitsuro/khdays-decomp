extern void func_ov022_02083f0c(void);
extern void func_ov022_02083c08(int arg0);
extern void func_02023c14(int arg0);
extern int data_ov022_020b2e60;
extern void func_ov022_02083904(void);
extern void func_ov022_02083bd8(void);

int func_ov022_0208310c(void) {
    func_ov022_02083f0c();
    func_ov022_02083c08(1);
    switch (*(char *)(*(int *)&data_ov022_020b2e60 + 0x3e)) {
    case 0:
        return (int)func_ov022_02083904;
    case 1:
        break;
    case 2:
        return (int)func_ov022_02083904;
    case 3:
        func_02023c14(1);
        return (int)func_ov022_02083bd8;
    }
    return 0;
}
