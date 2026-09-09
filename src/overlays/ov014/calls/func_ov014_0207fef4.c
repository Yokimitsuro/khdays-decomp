extern int func_ov002_0207687c(void);
extern void func_ov002_0207c67c(void *, int);
extern void func_ov002_0207c618(void *, int, int);
extern int func_ov002_02074460(int);
extern void func_ov002_02073ed0(int, int, int);
extern unsigned int func_020235d0(int, int);
extern void func_020235e8(unsigned int, unsigned int, unsigned int);
extern int func_ov002_0207cea4(void);

int func_ov014_0207fef4(char *this_)
{
    int frame;
    int complete;

    frame = func_ov002_0207687c();
    complete = 0;
    if ((*(unsigned char *)(this_ + 0x1b1) & 2) == 0)
        goto not_complete;
    {
        *(int *)((char *)this_ + 0x1cc) =
            *(int *)((char *)this_ + 0x1cc) + frame;
        frame = *(int *)((char *)this_ + 0x1cc);
        if (frame >= 0x24000) {
            frame = 0x24000;
            *(int *)((char *)this_ + 0x1cc) = frame;
            complete = 1;
        }
        if ((*(unsigned short *)((char *)this_ + 0x12) & 4) != 0)
            func_ov002_0207c67c((char *)this_ + 0x3c,
                                *(int *)((char *)this_ + 0x1cc));
    }
    if (complete == 0)
        goto not_complete;
    {
        int bits;
        *(unsigned char *)((char *)this_ + 0x1b3) = 2;
        func_ov002_0207c618((char *)this_ + 0x3c, 2, 0);
        *(unsigned char *)((char *)this_ + 0x1b1) &= ~2;
        frame = func_ov002_02074460(*(short *)((char *)this_ + 0x1d0));
        if (frame >= 0)
            func_ov002_02073ed0(*(short *)((char *)this_ + 0x1d0), 1, -1);
        bits = func_020235d0(*(unsigned short *)((char *)this_ + 0x14),
                             *(unsigned char *)((char *)this_ + 0x16));
        func_020235e8(*(unsigned short *)((char *)this_ + 0x14),
                      *(unsigned char *)((char *)this_ + 0x16),
                      (unsigned short)((bits & 0xffff0001) | 4));
        return (int)func_ov002_0207cea4;
    }
not_complete:
    return 0;
}
