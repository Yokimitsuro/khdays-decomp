extern void func_01ff9f00(unsigned int cmd, const void *src, unsigned int words);

struct Gfx0201571c {
    unsigned int cmd;       /* +0x00 */
    char _4[0xd0];
    unsigned int field_d4;  /* +0xd4 */
};

extern struct Gfx0201571c data_02047394;

void func_0201571c(void)
{
    unsigned int *p = (unsigned int *)&data_02047394;
    func_01ff9f00(*p, p + 1, 0x34);
    data_02047394.field_d4 &= ~1u;
    data_02047394.field_d4 &= ~2u;
}
