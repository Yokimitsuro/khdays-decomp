extern char *data_ov026_02091368;
extern void func_ov026_0208a24c(void);
extern void func_ov026_02086210(void);
extern void func_ov026_0208a774(void);
extern void func_ov026_0208b0bc(void);

void (*func_ov026_0208c564(void))(void)
{
    func_ov026_0208a24c();
    func_ov026_02086210();
    func_ov026_0208a774();
    *(int *)(data_ov026_02091368 + 0xc3d4) = 0;
    return func_ov026_0208b0bc;
}
