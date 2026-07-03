extern int func_ov022_02095524();
extern void func_0202accc();
extern void func_ov089_020bbc90();
extern void func_ov089_020bbd40();
extern void *data_ov089_020bc120;

void func_ov089_020bae80(void *this)
{
    char *obj = (char *)*(int *)&data_ov089_020bc120;
    if ((*(unsigned long long *)((char *)this + 0x464) & 0x10000ULL) == 0 &&
        func_ov022_02095524((char *)this + 0x22f8) == 0 &&
        *(int *)((char *)this + 0x6bc) != 0x2e) {
        func_0202accc((char *)this + 0xf10, 1, (char *)this + 0xff0, 0);
    }
    func_ov089_020bbc90(this, obj + 0x2c2c, *(short *)((char *)this + 0x2aba));
    func_ov089_020bbd40(this, obj + 0x2c2c);
}
