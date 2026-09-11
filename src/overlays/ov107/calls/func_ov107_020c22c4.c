typedef unsigned short u16;

extern int *func_01fffca8(int list, int stride, int max);
extern void func_ov107_020c2b94(int owner, int child);

void func_ov107_020c22c4(int owner, u16 *child) {
    u16 flags = *child;
    if (flags & 0x40) {
        *func_01fffca8(owner + 0x80, 4, 100) = (int)child;
    } else if (flags & 0x80) {
        *func_01fffca8(owner + 0xa8, 4, 110) = (int)child;
        if (*(void (**)(int, int))(owner + 0x14) != 0) {
            (*(void (**)(int, int))(owner + 0x14))(owner, 1);
        }
    } else if (flags & 2) {
        *func_01fffca8(owner + 0xd0, 4, 90) = (int)child;
        *(int *)((char *)child + 0x40) |= 4;
    }
    func_ov107_020c2b94(owner, (int)child);
}
