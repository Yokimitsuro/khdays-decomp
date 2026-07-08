extern void func_0201d214();
extern void func_0201d298();
extern void func_0201cdec();
extern int data_0204b620[];
extern int data_0204ad8c[];
void func_0201d178(int param_1)
{
    if (((*(int *)(param_1 + 0x110) << 0x1f) >> 0x1f) == 0)
        return;
    func_0201d214(param_1);
    (*(void (**)(int))(param_1 + 0x168))(param_1);
    func_0201d298(data_0204b620, param_1);
    if (*(int *)((char *)data_0204ad8c + 4) != 0)
        func_0201d298((void *)(*(int *)((char *)data_0204ad8c + 4) + 0x4e0), param_1);
    func_0201cdec(param_1);
}
