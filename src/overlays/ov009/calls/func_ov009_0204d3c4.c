extern char *data_ov009_020563e4[];
extern void func_ov009_0204cfbc(void);
extern void func_ov009_0204e750(int arg0);
extern void func_ov009_0204e82c(int arg0);

void func_ov009_0204d3c4(void)
{
    func_ov009_0204cfbc();
    func_ov009_0204e750(*(int *)(data_ov009_020563e4[1] + 0x959c));
    func_ov009_0204e82c(*(int *)(data_ov009_020563e4[1] + 0x95a0));
}
