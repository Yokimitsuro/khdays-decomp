extern int func_02032f5c(void);
extern int func_ov023_02083ad0(int);
extern void func_02020888(int a, void *b, int c);
extern void func_02023008(void);
extern void func_02022d7c(void);

void func_02022fe4(void)
{
    if (func_ov023_02083ad0(func_02032f5c()) != 0) {
        func_02020888(1, (void *)func_02022d7c, 0);
        func_02023008();
    }
}
