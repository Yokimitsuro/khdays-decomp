extern int func_ov002_0206da70(int);
extern int func_0202b930(void *, int, int, int);
extern void func_ov014_0207fa40(int, int);
extern unsigned int func_020235d0(int, int);
extern void func_0202bedc(unsigned char *, int);

void func_ov014_0207fb04(int this_)
{
    unsigned short flags = *(unsigned short *)(this_ + 0x12);
    int sub = *(int *)(this_ + 8);
    flags |= 4;
    *(unsigned short *)(this_ + 0x12) = flags;
    int model = func_ov002_0206da70(sub + 0x58);
    func_0202b930((void *)(this_ + 0x2c), model, 1, 4);
    unsigned short animation = *(unsigned short *)(this_ + 0x18);
    if ((*(int *)(this_ + 0x38) & 0x20) == 0) {
        *(unsigned short *)(this_ + 0xb8) = animation;
        *(unsigned short *)(this_ + 0x3c) |= 0x20;
    }
    func_ov014_0207fa40(this_, *(unsigned char *)(this_ + 0x1b3));
    int flag;
    if (func_020235d0(*(unsigned short *)(this_ + 0x14),
                      *(unsigned char *)(this_ + 0x16)) & 1)
        flag = 1;
    else
        flag = 0;
    func_0202bedc((unsigned char *)(this_ + 0x2c), flag);
}
