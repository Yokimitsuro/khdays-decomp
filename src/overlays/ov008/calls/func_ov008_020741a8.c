extern int func_ov008_02050e5c(void);
extern int func_ov008_0207410c(int arg0, int arg1);
extern int func_ov008_02050e8c(void);
extern void func_ov008_02074150(int arg0, int arg1, int arg2, int arg3);

void func_ov008_020741a8(int arg0, int arg1, int arg2)
{
    func_ov008_0207410c(arg0, func_ov008_02050e5c());
    func_ov008_02074150(arg0, arg1, arg2, func_ov008_02050e8c());
}
