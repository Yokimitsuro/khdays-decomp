/* func_ov222_020d61c0 -- begin a homing move toward a freshly acquired target.
 * VARIADIC: the caller passes the mode plus a destination Vec3 by value, and then more varargs
 * behind it. The prologue's stmdb {r0,r1,r2,r3} and the bare `add sp,sp,#0x10` in the epilogue
 * are the tell. Nothing happens without a target from func_ov107_020cab14.
 * With one: the mode goes to +0x58, the destination Vec3 to +0x24, the tuning constants at
 * data_02041dc8 to +0x18, the curve at +0x30 is primed by func_0202ed60 from data_02042258 and
 * whatever varargs follow the Vec3, the progress fields (+0x48/+0x54/+0x5c/+0x60) are zeroed,
 * and the owner is put in state 1.
 *
 * ★ THE VA_START LEVER (shared with its caller func_ov221_020d3f38, which had the same residue).
 * Parked at one instruction: the ROM caches the mode out of its argument register (`mov r5,r1`)
 * while mwcc read it back from the block the variadic prologue had just spilled
 * (`ldr r5,[sp,#0x14]`). The cause is that `va_start(ap, mode)` takes `&mode`, which marks the
 * parameter address-taken, and from there mwcc treats the spilled copy as canonical. The fix is
 * to never take the address of a parameter that is actually used: NAME the varargs you need.
 * The destination Vec3 becomes a by-value parameter and the following vararg becomes a named
 * `rest` whose address is the va_list -- same addresses (sp+0x18 and sp+0x24), no address ever
 * taken of `mode`, and both `mov r4,r0` / `mov r5,r1` come back.
 * Naming them also kills a second-order problem: reached through an advancing `ap`, mwcc keeps
 * the va pointer in a register and computes the second address as `add r2,ip,#0xc`, where the
 * ROM materialises `add r2,sp,#0x24` from scratch. Two independent named parameters give two
 * independent frame offsets.
 *
 * Still true and worth keeping: the `m = mode` local is what earns r5 and makes the prologue push
 * {r3,r4,r5,lr}; using the parameter directly gives push {r4,lr} and a 4-byte-larger frame.
 */
typedef struct {
    int x;
    int y;
    int z;
} Vec3;



extern int func_ov107_020cab14(int owner, int kind);
extern void func_0202ed60(Vec3 *curve, const Vec3 *src, char *ap);
extern Vec3 data_02041dc8;
extern Vec3 data_02042258;

void func_ov222_020d61c0(int *ctx, int mode, Vec3 dest, int rest, ...) {
    int m;

    m = mode;
    ctx[0x10] = func_ov107_020cab14(ctx[0], 0);
    if (ctx[0x10] == 0) {
        return;
    }
    ctx[0x16] = m;
    ctx[0x17] = 0;

    *(Vec3 *)((char *)ctx + 0x24) = dest;
    *(Vec3 *)((char *)ctx + 0x18) = data_02041dc8;
    ctx[0x18] = 0;
    func_0202ed60((Vec3 *)((char *)ctx + 0x30), &data_02042258, (char *)&rest);

    ctx[0x15] = 0;
    ctx[0x12] = 0;
    *(unsigned char *)(ctx[0] + 0x1c7) = 1;
}
