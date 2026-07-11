extern int func_02021980(void *a, void *b);
extern void func_ov002_0207679c(unsigned char a, unsigned short b);
extern void func_ov017_02080a68(void);

int func_ov017_02080dd0(void *arg1, char *arg2) {
    int a = func_02021980(arg1, arg2);
    int b = func_02021980(arg1, arg2 + 8);
    func_ov002_0207679c((unsigned char)a, (unsigned short)b);
    func_ov017_02080a68();
    return 1;
}
