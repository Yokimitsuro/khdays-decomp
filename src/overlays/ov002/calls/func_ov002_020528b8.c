extern int func_ov002_02052844(int arg0, int arg1);
extern void func_020262bc(int arg0, int arg1, int arg2, int arg3);

int func_ov002_020528b8(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    int value = func_ov002_02052844(arg0, arg1);
    func_020262bc(arg2, arg3, value, arg4);
    return arg2;
}
