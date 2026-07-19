extern int func_02023588(int flag);
extern int func_020235a8(int flag);
extern int func_ov002_0206b7a4(void);
extern void func_ov022_02083fa4(int a);
extern void func_ov002_0206db5c(void);

extern int data_ov002_0207fa00;
extern unsigned char data_0204c240;

int func_ov002_0206ce78(void) {
    char *ctx = *(char **)&data_ov002_0207fa00;

    if (func_02023588(0x2086) == 0 && func_ov002_0206b7a4() == 0) {
        func_020235a8(0x2086);
        if (*(short *)(ctx + 0x8ca4) > 0) {
            func_ov022_02083fa4(1);
        }
        if ((data_0204c240 & 4) != 0 && func_02023588(0x20e8) == 0) {
            func_ov002_0206db5c();
        }
    }
    return func_02023588(0x2086);
}
