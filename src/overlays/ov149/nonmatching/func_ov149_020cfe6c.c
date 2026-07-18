/* NONMATCHING -- 204 vs 208 B, one instruction. Head of a 5-member family (208 B).
 * All the forms are right (hw60 `hi |= 1` EXPLICIT then `hi &= ~0x8c` BITFIELD, the byte
 * field at +8, the vec3 whole-struct copy). The ROM computes the copy source with a separate
 * `add r0, r0, #0x394` before the `ldm` and materialises 0x500 into ip early, holding it
 * across the hw60 work; mwcc folds the add away and materialises the constant late.
 * Ruled out: a local `int k = 0x500` shared by the store and the call argument, and an
 * explicit `struct vec *src` for the copy source. */
struct vec { int x, y, z; };
typedef struct { unsigned short lo : 8, hi : 8; } Hw60;
typedef struct { unsigned int lo : 8, rest : 24; } Byte8;
extern void func_01ffa724();
extern void func_0203c634(int self, int index, void *cb);
extern void func_ov149_020cff3c(void);

void func_ov149_020cfe6c(int self) {
    int *obj = *(int **)(self + 4);
    unsigned short w;

    obj[9] = 0;
    w = *(unsigned short *)(*obj + 0x60);
    *(unsigned short *)(*obj + 0x60) =
        (unsigned short)((w & ~0xff00)
                         | (((((unsigned int)w << 0x10) >> 0x18 | 1) << 0x18) >> 0x10));
    ((Hw60 *)(*obj + 0x60))->hi &= ~0x8c;
    ((Byte8 *)(*(int *)(*obj + 0x388) + 8))->lo |= 1;
    *(struct vec *)(obj + 5) = *(struct vec *)(*obj + 0x394);
    obj[8] = 0x500;
    func_01ffa724(0x500, obj + 5, obj + 2);
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov149_020cff3c);
}
