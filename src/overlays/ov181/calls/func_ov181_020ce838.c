extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(int *self, int idx, void *cb);
extern void func_ov181_020ce8d4(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned int f : 8; };

void func_ov181_020ce838(int *self) {
    int *s = (int *)self[1];
    *(unsigned short *)(*s + 0x100 + 0xae) |= 1;
    ((struct b8 *)(*(int *)(*s + 0x388) + 8))->f &= ~1;
    ((struct hw60 *)(*s + 0x60))->hi |= (unsigned char)2;
    func_ov107_020c9264(*s, 5, 0);
    s[7] = 0;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), (void *)&func_ov181_020ce8d4);
}
