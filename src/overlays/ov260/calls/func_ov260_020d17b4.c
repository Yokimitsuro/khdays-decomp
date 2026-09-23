/* Place an ov260 part at `at` (020c5c54), tell its +0xc handler when +0x40 bit 1 allows it, restart
 * the +0x384 model's frame, store the +0x3a0 anchor from `anchor` and set bit 0 of the +0x60 high
 * byte. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
struct Flags40 { int b0 : 1; int b1 : 1; };

extern void func_ov107_020c5c54(char *actor, Vec3 *at);
extern void func_0203c7ac(int item, int a);

void func_ov260_020d17b4(char *self, Vec3 *at, Vec3 *anchor)
{
    func_ov107_020c5c54(self, at);
    if (((struct Flags40 *)(self + 0x40))->b1 && *(void (**)(char *, int))(self + 0xc) != 0) {
        (*(void (**)(char *, int))(self + 0xc))(self, 0);
    }
    func_0203c7ac(*(int *)(self + 0x384), 0);
    *(Vec3 *)(self + 0x3a0) = *anchor;
    {
        u16 hw = *(u16 *)(self + 0x60);
        *(u16 *)(self + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
}
