extern void *func_0203d15c();
extern void func_01fffc24();
extern void *func_01fffca8();
extern int func_0203bdfc();
short *func_0203bee8(int param_1, short param_2, unsigned short *param_3)
{
    short *e;
    if (*(int *)(param_1 + 0x90) == 0) {
        void *p = func_0203d15c(0x28);
        *(void **)(param_1 + 0x90) = p;
        func_01fffc24(p);
    }
    e = (short *)func_01fffca8(*(int *)(param_1 + 0x90), 0x30, 100);
    *e = param_2;
    e[1] = (short)func_0203bdfc(param_1, param_3);
    return e;
}
