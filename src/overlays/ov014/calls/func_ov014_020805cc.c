extern void *func_ov002_02076a38(void *pool, int index);
extern void func_ov002_02076480(int idx, int *node);
extern void func_ov014_02080464(void);
typedef struct { int x, y, z; } Vec;

void *func_ov014_020805cc(void *pool, unsigned short b, unsigned short c,
                          unsigned short d, unsigned char e, void *vec, int g) {
    Vec *v = (Vec *)vec;
    unsigned char *entry = (unsigned char *)func_ov002_02076a38(pool, b);
    *(Vec *)(entry + 0xd0) = *v;
    *(unsigned short *)(entry + 0xa8) = (unsigned short)g;
    *(unsigned short *)(entry + 0x2c) |= 0x20;
    *(unsigned short *)(entry + 0x18) = (unsigned short)g;
    *(Vec *)(entry + 0x1c) = *v;
    *(int *)(entry + 0x28) = *(int *)((char *)pool + 0x68);
    entry[0x135] = 0;
    entry[0x134] = 0;
    entry[0x10] = (unsigned char)c;
    *(void **)(entry + 0xc) = func_ov014_02080464;
    *(unsigned short *)(entry + 0x12) |= 8;
    *(unsigned short *)(entry + 0x14) = d;
    entry[0x16] = (unsigned char)e;
    entry[0x17] = 3;
    func_ov002_02076480(c, (int *)entry);
    return entry;
}
