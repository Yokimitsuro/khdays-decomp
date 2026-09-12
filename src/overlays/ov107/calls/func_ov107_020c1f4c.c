typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct { u16 f0; u8 f2; u8 f3; } LocalBuf;

extern void func_02031384(int id, LocalBuf *buf, int count);

void func_ov107_020c1f4c(char *self, char *other) {
    LocalBuf buf = {0, 0, 0};

    *(u32 *)(self + 0xf8) = (*(u32 *)(self + 0xf8) & ~0xf) | 1;
    *(char **)(self + 0xfc) = other;

    buf.f0 = *(u16 *)(self + 2);
    buf.f2 = 1;
    buf.f3 = (u8)*(u16 *)(other + 2);

    func_02031384(4, &buf, 4);

    *(u32 *)(other + 0x40) &= ~4;
}
