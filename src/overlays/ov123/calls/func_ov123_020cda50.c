extern void func_0203c634(int *self, int idx, void *cb);
extern void func_ov123_020cdae4(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned int f : 8; };

void func_ov123_020cda50(int *self) {
    int *s = (int *)self[1];
    ((struct hw60 *)(*s + 0x60))->hi &= ~1;
    ((struct hw60 *)(*s + 0x60))->hi |= (unsigned char)0x82;
    ((struct b8 *)(*(int *)(*s + 0x388) + 8))->f &= ~1;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), (void *)&func_ov123_020cdae4);
}
