extern void func_0201e12c(void *p);
extern void func_0201e144(void *p, int a, int b);

void func_0201a680(void *self)
{
    char *p = (char *)self;
    *(unsigned char *)(p + 0x2e) = 0;
    *(unsigned char *)(p + 0x2d) = 0;
    *(unsigned char *)(p + 0x2f) = 0;
    *(unsigned short *)(p + 0x34) = 0;
    *(unsigned short *)(p + 0x3e) = 0;
    *(unsigned char *)(p + 0x40) = 0x7f;
    *(unsigned char *)(p + 0x41) = 0x7f;
    func_0201e12c(p + 0x1c);
    func_0201e144(p + 0x1c, 0x7f00, 1);
}
