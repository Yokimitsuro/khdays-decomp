/* NONMATCHING -- 184 vs 180 B, ONE instruction. Head of a 5-member family (180 B).
 *
 * The ROM does the load and the pointer advance in a single POST-INDEXED load:
 *     ldr r0, [r4], #0x18      ; owner = *obj, then obj += 6 ints
 * and then reuses the advanced r4 as the destination base of the second struct copy.
 * mwcc always splits it into a load plus a separate `add`.
 *
 * Ruled out: `obj += 6` after reading `*obj`; a `struct vec *p = (struct vec *)obj; p += 2;`
 * walk; and plain `obj + 6` offsets in both copies.
 *
 * SOLVED on the way -- do NOT rediscover:
 *  - `v = obj[3] = func_0203d040(...)` in that order: the ROM stores the raw r0 and keeps
 *    the copy, so `obj[3] = v;` as a separate statement is wrong.
 *  - declaration order `r` before `q` puts q at sp+0x10 and r at sp+0, the ROM layout.
 *  - the two 12-byte moves are whole-struct assignments (ldm/stm), not field-by-field.
 */
struct vec { int x, y, z; };
struct quat { int x, y, z, w; };
extern int  func_0203d040();
extern void func_0202f188();
extern void func_0202ed60();
extern void func_0202ef54();
extern void func_0203c9d0();
extern struct quat data_02042264;
extern struct vec data_02041dc8;

void func_ov194_020ccb78(int *self) {
    int *obj = (int *)self[1];
    struct quat r;
    struct quat q;
    int v;

    v = obj[3] = func_0203d040(obj[3], obj[4], obj[5], 0);
    func_0202f188(&r, &data_02042264, v);
    func_0202ed60(&q, &data_02042264, *obj + 0x124);
    func_0202ef54(&q, &q, &r);
    func_0203c9d0(*obj + 0xa0, &q);
    if (obj[0xd] > 0) {
        obj[0xd] = obj[0xd] - *(int *)(self[0] + 0x2c);
    }
    *(struct vec *)(*obj + 0xf0) = *(struct vec *)(obj + 6);
    *(struct vec *)(obj + 6) = data_02041dc8;
}
