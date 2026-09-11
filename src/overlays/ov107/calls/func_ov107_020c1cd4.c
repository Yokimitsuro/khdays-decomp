typedef unsigned int u32;

extern void MI_CpuFill8(void *dst, u32 data, u32 size);

typedef struct {
    unsigned char state;      /* +0x00 */
    signed char pad0b : 2;
    signed char field : 4;    /* +0x01, bits 2-5 */
    signed char pad1b : 2;
    char pad[10];
} Slot;

void func_ov107_020c1cd4(void *obj) {
    int i;
    Slot *fillDst = (Slot *)((char *)obj + 0x50);
    unsigned char *sb = (unsigned char *)obj;
    signed char *bitp = (signed char *)obj + 0x51;

    for (i = 0; i < 8; i++) {
        MI_CpuFill8(fillDst, 0, 0xc);
        sb[0x50] = 0xff;
        *bitp = (*bitp & ~0x3c) | 0x3c;
        bitp += 0xc;
        fillDst += 1;
        sb += 0xc;
    }
    *(unsigned short *)((char *)obj + 0x4c) = 0;
}
