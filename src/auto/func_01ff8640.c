struct DmaChannel {
    unsigned int src;
    unsigned int dst;
    unsigned int ctrl;
};

void func_01ff8640(int ch, unsigned int src, unsigned int dst, unsigned int ctrl)
{
    struct DmaChannel *p = (struct DmaChannel *)0x40000b0;
    volatile unsigned int *q = &p[ch].dst;
    p[ch].src = src;
    q[0] = dst;
    q[1] = ctrl;
}
