extern void func_ov022_0209fb60();
extern void func_ov022_0209fb98();

void func_ov070_020b8390(char *p)
{
    func_ov022_0209fb60(p, 0, 1);
    func_ov022_0209fb98(p, 0, 1);
    if (*(signed char *)(p + 0xDA9) != 0) {
        ((unsigned char *)p)[0xDA8] |= 1;
    }
    func_ov022_0209fb60(p, 1, 2);
    func_ov022_0209fb98(p, 1, 1);
    if (*(signed char *)(p + 0xF0D) != 0) {
        ((unsigned char *)p)[0xF0C] |= 1;
    }
}
