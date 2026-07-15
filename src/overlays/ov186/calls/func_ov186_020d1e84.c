/* c634 init: reset owner status bytes (+0x1c6=0, +0x1c7=-1), clear bit0 of the low byte at
 * *(owner+0x388)+8, cache owner+0x74 into obj[0x11] and (owner->f384)+0xad into obj[0x12],
 * set owner hw60 hi bits 6, seed obj[2..5] from a shared constant vec (data_020420f8) and
 * mirror it into obj[6..9], then arm the three phase callbacks (slots 1/0/2). */
struct vec4 { int a, b, c, d; };
struct b8 { unsigned int b : 8; };
extern const struct vec4 data_020420f8;
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov186_020d2284(void);
extern void func_ov186_020d1f70(void);
extern void func_ov186_020d2180(void);
void func_ov186_020d1e84(int self) {
    int *obj = *(int **)(self + 4);
    *(char *)(*obj + 0x1c6) = 0;
    *(char *)(*obj + 0x1c7) = -1;
    ((struct b8 *)(*(int *)(*obj + 0x388) + 8))->b &= ~1;
    obj[0x11] = *obj + 0x74;
    obj[0x12] = *(int *)(*obj + 0x384) + 0xad;
    {
        unsigned short v = *(unsigned short *)(*obj + 0x60);
        *(unsigned short *)(*obj + 0x60) =
            (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 6) << 0x18) >> 0x10));
    }
    *(struct vec4 *)(obj + 2) = data_020420f8;
    *(struct vec4 *)(obj + 6) = *(struct vec4 *)(obj + 2);
    func_0203c634(self, 1, &func_ov186_020d2284);
    func_0203c634(self, 0, &func_ov186_020d1f70);
    func_0203c634(self, 2, &func_ov186_020d2180);
}
