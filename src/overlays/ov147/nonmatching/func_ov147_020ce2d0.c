/* NONMATCHING -- 188/188 B. All four forms are right (hw60 `hi |= 0x80` EXPLICIT, hw60
 * `hi &= ~1` BITFIELD -- the two opposite forms back to back -- the byte field at +8, and the
 * vec3 whole-struct copy). What differs is SCHEDULING and register pressure: the ROM loads
 * the vec3 early into caller-saved r0/r1/r2 (`ldm r0,{r0,r1,r2}` at +0x28) and computes the
 * destination `add r5, ip, #8` early too, spending three callee-saved registers; mwcc defers
 * the load to the end and spends one.
 *
 * Head of a 5-member family (188 B).
 *
 * Ruled out 2026-07-18: three separate int locals loaded up front (+4 B), a local `struct vec`
 * copied early and stored late (+20 B -- mwcc gives it a stack slot), hoisting the destination
 * into a `struct vec *dst` declared at the top, and simply moving the copy statement above the
 * hw60 block. None of them moves the ldm. */
struct vec { int x, y, z; };
typedef struct { unsigned short lo : 8, hi : 8; } Hw60;
typedef struct { unsigned int lo : 8, rest : 24; } Byte8;
extern void func_0203c634(int self, int index, void *cb);
extern struct vec data_02041dc8;
extern void func_ov147_020ce38c(void);

void func_ov147_020ce2d0(int self) {
    int *obj = *(int **)(self + 4);
    unsigned short w;

    *(int *)(*obj + 0x38c) = 0;
    w = *(unsigned short *)(*obj + 0x60);
    *(unsigned short *)(*obj + 0x60) =
        (unsigned short)((w & ~0xff00)
                         | (((((unsigned int)w << 0x10) >> 0x18 | 0x80) << 0x18) >> 0x10));
    ((Hw60 *)(*obj + 0x60))->hi &= ~1;
    ((Byte8 *)(*(int *)(*obj + 0x388) + 8))->lo &= ~1;
    *(struct vec *)(obj + 2) = data_02041dc8;
    func_0203c634(self, *(signed char *)(self + 0x20), &func_ov147_020ce38c);
}
