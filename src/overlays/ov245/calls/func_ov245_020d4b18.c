/* func_ov245_020d4b18 -- pose sync of the mounted actor: the +0xa0 placement takes the +0x398
 * rider's +0x44c anchor's +4 rotation, the +0x39c seat's +0x2c offset is rotated through it and
 * added to the +0x3a0 position, then the anchor's +0x14 position is added; the owner is notified
 * (020c5c54), the seat's motion runs (020c9ec8) and the base sync (020c6980) finishes. */
typedef struct { int x, y, z; } Vec3;

extern void func_0203c9d0(int placement, void *rotation);
extern void func_0202f384(Vec3 *out, void *rotation, const Vec3 *in);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov107_020c5c54(int self, Vec3 *v);
extern void func_ov107_020c9ec8(int item, int a);
extern void func_ov107_020c6980(int self, int a);

void func_ov245_020d4b18(int self, int a) {
    Vec3 off;

    func_0203c9d0(self + 0xa0, (void *)(*(int *)(*(int *)(self + 0x398) + 0x44c) + 4));
    func_0202f384(&off, (void *)(self + 0xa0), (Vec3 *)(*(int *)(self + 0x39c) + 0x2c));
    VEC_Add((Vec3 *)(self + 0x3a0), &off, (Vec3 *)(self + 0x3a0));
    VEC_Add((Vec3 *)(self + 0x3a0), (Vec3 *)(*(int *)(*(int *)(self + 0x398) + 0x44c) + 0x14), &off);
    func_ov107_020c5c54(self, &off);
    func_ov107_020c9ec8(*(int *)(self + 0x39c), a);
    func_ov107_020c6980(self, a);
}
