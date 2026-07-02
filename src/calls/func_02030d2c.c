extern int func_01fff99c(int x);
extern void func_01fffa60(int a, int b, int c, int d);
void func_02030d2c(int param_1, int param_2) {
    int t = func_01fff99c((unsigned int)((unsigned int)*(unsigned short *)param_1 << 0x1a) >> 0x1b);
    func_01fffa60(param_1, param_2, t, 0);
}
