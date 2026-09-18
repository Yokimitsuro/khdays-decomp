/* State init of the ov250 enemy (and its byte-identical twin): resets the sub-state (+0x1c6 0,
 * +0x1c7 pending -1), clears bit 0 of the +0x388 item's +8 flags, points the +4/+8 slots at the
 * actor's +0xb0/+0x74 vectors and +0xc at the +0x384 item's +0xad byte, clears +0x394, sets bits
 * 1/2 of the +0x60 high byte and installs the three state callbacks (slots 1, 0, 2). */
extern void func_0203c634(int *self, int idx, void *cb);
extern void func_ov251_020d43c4(void);
extern void func_ov251_020d4118(void);
extern void func_ov251_020d4310(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned int f : 8; };

void func_ov251_020d403c(int *self) {
    int *s = (int *)self[1];
    int zero = 0;
    *(signed char *)(*s + 0x1c6) = zero;
    *(signed char *)(*s + 0x1c7) = zero - 1;
    ((struct b8 *)(*(int *)(*s + 0x388) + 8))->f &= ~1;
    s[1] = *s + 0xb0;
    s[2] = *s + 0x74;
    s[3] = *(int *)(*s + 0x384) + 0xad;
    *(int *)(*s + 0x394) = zero;
    ((struct hw60 *)(*s + 0x60))->hi |= (unsigned char)6;
    func_0203c634(self, 1, (void *)&func_ov251_020d43c4);
    func_0203c634(self, 0, (void *)&func_ov251_020d4118);
    func_0203c634(self, 2, (void *)&func_ov251_020d4310);
}
