extern void MIi_CpuCopy16(const void *src, void *dst, unsigned int size);

typedef struct Struct02013340 {
    unsigned short field_0;
    unsigned char pad[10];
} Struct02013340;

void func_02013340(unsigned short *r0, Struct02013340 *r1, int r2, int r3,
                   int a5, int a6, int a7, unsigned int a8, int a9) {
    unsigned int stride;
    int i;
    int end;
    int dst_off;
    unsigned int copy_bytes;
    unsigned short *src;
    unsigned short *dst;

    stride = (unsigned int)r1->field_0 >> 3;
    r1++;
    dst_off = a6 * a7 + a5;
    copy_bytes = a8 * 2;
    end = r3 + a9;
    src = (unsigned short *)r1 + (r2 + r3 * stride);
    dst = r0 + dst_off;
    for (i = r3; i < end; i++) {
        MIi_CpuCopy16(src, dst, copy_bytes);
        src += stride;
        dst += a7;
    }
}
