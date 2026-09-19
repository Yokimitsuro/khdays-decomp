/* func_ov160_020cf0c0 -- c634 handler: arm the owner for a dash/lunge and hand off to
 * func_ov160_020cf1a4.
 *
 * Zeroes the object's +0x28 distance, sets bit 0 of the owner's +0x60 config high byte and
 * then clears bits 0x8c of it, sets bit 0 of the byte at *(owner+0x388)+8, sets obj[9] =
 * 0x1000 as the length, builds the +0x14 rotation from data_02042258 to the owner's +0x394
 * basis (ed60), turns data_02042258 by it into obj[2..4] (f384), scales that by the length
 * and dispatches the next state.
 *
 * The +0x60 half-word is a bitfield (unsigned short lo:8, hi:8); the |= 1 edit is spelled out
 * because the bitfield form adds a truncation the ROM does not have here. */
struct hw60 { unsigned short lo:8, hi:8; };
struct b8 { unsigned int b:8; };
struct vec { int x, y, z; };
struct quat { int q[4]; };
extern void func_0202ed60(struct quat *out, const struct vec *from, void *basis);
extern void func_0202f384(struct vec *out, struct vec *basis, const void *v);
extern void func_01ffa724(int scale, struct vec *v, struct vec *out);
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov160_020cf1a4(void);
extern const struct vec data_02042258;
void func_ov160_020cf0c0(int self) {
    int *obj = *(int **)(self + 4);
    obj[10] = 0;
    {
        unsigned short v = *(unsigned short *)(*obj + 0x60);
        *(unsigned short *)(*obj + 0x60) =
            (unsigned short)((v & ~0xff00) | (((((unsigned int)v << 0x10) >> 0x18 | 1) << 0x18) >> 0x10));
    }
    ((struct hw60 *)(*obj + 0x60))->hi &= ~0x8c;
    ((struct b8 *)(*(int *)(*obj + 0x388) + 8))->b |= 1;
    obj[9] = 0x1000;
    func_0202ed60((struct quat *)(obj + 5), &data_02042258, (void *)(*obj + 0x394));
    func_0202f384((struct vec *)(obj + 2), (struct vec *)(obj + 5), (void *)&data_02042258);
    func_01ffa724(obj[9], (struct vec *)(obj + 2), (struct vec *)(obj + 2));
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov160_020cf1a4);
}
