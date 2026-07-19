extern void func_0203c634(int *self, int idx, void *cb);
extern void func_ov184_020d2774(void);
extern void func_ov184_020d24c8(void);
extern void func_ov184_020d26c0(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned int f : 8; };

void func_ov184_020d23ec(int *self) {
    int *s = (int *)self[1];
    int zero = 0;
    *(signed char *)(*s + 0x1c6) = zero;
    *(signed char *)(*s + 0x1c7) = zero - 1;
    ((struct b8 *)(*(int *)(*s + 0x388) + 8))->f &= ~1;
    s[1] = *s + 0xb0;
    s[2] = *s + 0x74;
    s[3] = *(int *)(*s + 0x384) + 0xad;
    *(int *)(*s + 0x394) = 1;
    ((struct hw60 *)(*s + 0x60))->hi |= (unsigned char)6;
    func_0203c634(self, 1, (void *)&func_ov184_020d2774);
    func_0203c634(self, 0, (void *)&func_ov184_020d24c8);
    func_0203c634(self, 2, (void *)&func_ov184_020d26c0);
}
