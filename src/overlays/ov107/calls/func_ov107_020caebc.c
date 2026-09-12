struct T { int a, b, c; };

extern struct T data_02041dc8;
extern void func_ov107_020c4eb4(void *self, int region);

void func_ov107_020caebc(void *self, int region)
{
    unsigned short *p = (unsigned short *)((char *)self + 0x60);
    unsigned int h = *p;
    unsigned int lo = h & ~0xff00;
    unsigned short hi = (unsigned short)(((h << 0x10) >> 0x18) & ~1);
    struct T local;

    *p = lo | (((unsigned int)hi << 0x18) >> 0x10);

    local = data_02041dc8;
    *(struct T *)((char *)self + 0x1a8) = local;
    *(struct T *)((char *)self + 0xfc) = local;

    func_ov107_020c4eb4(self, region);
}
