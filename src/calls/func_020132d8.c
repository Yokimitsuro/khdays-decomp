extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);

typedef struct Struct020132d8 {
    unsigned short field_0;
    unsigned char pad[10];
} Struct020132d8;

void func_020132d8(unsigned char *r0, Struct020132d8 *r1, int r2, int r3,
                   int a5, int a6, int a7, unsigned int a8, int a9) {
    unsigned int stride;
    int i;
    int end;
    int src_off;
    int dst_off;
    unsigned char *src;
    unsigned char *dst;

    stride = (unsigned int)r1->field_0;
    r1++;
    dst_off = a6 * a7 + a5;
    stride >>= 3;
    src_off = r3 * stride + r2;
    end = r3 + a9;
    src = (unsigned char *)r1 + src_off;
    dst = r0 + dst_off;
    for (i = r3; i < end; i++) {
        MI_CpuCopy8(src, dst, a8);
        src += stride;
        dst += a7;
    }
}
