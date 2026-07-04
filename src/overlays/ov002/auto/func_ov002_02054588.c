int func_ov002_02054588(int a0, int dst, int src)
{
    *(unsigned short *)(dst + 6) = *(unsigned short *)(src + 6);
    *(unsigned short *)(dst + 8) = *(unsigned short *)(src + 8);
    *(short *)(dst + 0xa) = *(short *)(src + 0xa);
    *(short *)(dst + 0xc) = *(short *)(src + 0xc);
    *(int *)(dst + 0x18) = *(int *)(src + 0x18);
    return dst;
}
