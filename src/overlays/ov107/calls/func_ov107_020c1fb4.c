/* Builds a 4-byte panel-refresh packet and forwards it via func_02031384, but only when bit 2
 * of the entry's flags at +0x40 is set; clears that bit afterward. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    int pad[16];
    signed int b0:1;
    signed int b1:1;
    signed int b2:1;
} EntFlags;

extern int func_02031384(int a, void *buf, int b);

typedef struct { u16 a; u16 b; } Buf2;

void func_ov107_020c1fb4(int obj, int *ent) {
    unsigned char buf[4];
    Buf2 *p = (Buf2 *)buf;
    p->a = 0;
    p->b = 0;
    if (((EntFlags *)ent)->b2 == 0) {
        return;
    }
    *(int *)(obj + 0xf8) = (*(int *)(obj + 0xf8) & ~0xf) | 2;
    *(int *)(obj + 0xfc) = (int)ent;
    *(u16 *)&buf[0] = *(u16 *)(obj + 2);
    buf[2] = 3;
    buf[3] = (u8)(*(u16 *)(*(int *)(obj + 0xfc) + 2));
    func_02031384(4, p, 4);
    *(int *)((char *)ent + 0x40) &= ~4;
}
