void func_ov025_020ae49c(void) {
    unsigned int *p = (unsigned int *)0x04001000;
    *p = *p & 0xffffe0ff | 0x1f00;
    *(unsigned short *)(p + 2) &= ~3;
    *(unsigned short *)((int)p + 10) = *(unsigned short *)((int)p + 10) & ~3 | 1;
    *(unsigned short *)(p + 3) = *(unsigned short *)(p + 3) & ~3 | 2;
    *(unsigned short *)((int)p + 0xe) = *(unsigned short *)((int)p + 0xe) & ~3 | 3;
}
