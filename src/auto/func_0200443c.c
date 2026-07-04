struct src_word { unsigned int low_nibble : 4; };

void func_0200443c(void *dst, int a, unsigned int *src) {
    *(int *)dst = a;
    *(int *)((char *)dst + 4) = src[0] >> 8;
    *(char *)((char *)dst + 0xf) = 0;
    *(char *)((char *)dst + 0x10) = 0;
    *(int *)((char *)dst + 8) = 0;
    *(char *)((char *)dst + 0x11) = 3;
    *(short *)((char *)dst + 0xc) = 0;
    *(char *)((char *)dst + 0xe) = 0;
    *(char *)((char *)dst + 0x12) = ((struct src_word *)src)->low_nibble != 0;
}
