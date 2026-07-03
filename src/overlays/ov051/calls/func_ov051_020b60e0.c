extern int func_ov022_02095524();
extern void func_0202accc();
extern void func_ov051_020b6ef0();
extern void func_ov051_020b6fa0();
extern void *data_ov051_020b7380;

void func_ov051_020b60e0(void *this)
{
    char *obj = (char *)*(int *)&data_ov051_020b7380;
    if ((*(unsigned long long *)((char *)this + 0x464) & 0x10000ULL) == 0 &&
        func_ov022_02095524((char *)this + 0x22f8) == 0 &&
        *(int *)((char *)this + 0x6bc) != 0x2e) {
        func_0202accc((char *)this + 0xf10, 1, (char *)this + 0xff0, 0);
    }
    func_ov051_020b6ef0(this, obj + 0x2c2c, *(short *)((char *)this + 0x2aba));
    func_ov051_020b6fa0(this, obj + 0x2c2c);
}
