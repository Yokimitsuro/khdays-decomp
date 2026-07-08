extern int func_0201717c();
extern int *func_02017124();
extern void func_02018fe0();
extern int *func_02017150();
extern void func_020190b8();
void func_02019120(int param_1, int *param_2, unsigned int param_3)
{
    int obj = param_2[2];
    int r = func_0201717c(obj, param_3 & 0xffff, (unsigned int)(*param_2 << 4) >> 0x10);
    int *e = func_02017124(obj, *(unsigned char *)(r + 2));
    func_02018fe0(param_2[5], e, param_1);
    if (*(unsigned char *)(r + 3) == 0xff)
        return;
    e = func_02017150(obj, *(unsigned char *)(r + 3));
    func_020190b8(param_2[5], e, param_1);
}
