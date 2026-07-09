extern void func_ov008_02050cd4(void);
extern unsigned char data_ov008_0209059f[];
int func_ov008_02069bc8(int index)
{
    func_ov008_02050cd4();
    return data_ov008_0209059f[index * 0x14];
}
