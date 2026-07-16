/* func_ov221_020d43a0 -- begin a homing move toward a freshly acquired target.
 * VARIADIC: the caller passes the mode plus a Vec3 by value. The prologue's
 * stmdb {r0,r1,r2,r3} and the bare `add sp,sp,#0x10` in the epilogue are the tell.
 * Nothing happens without a target from func_ov107_020cab14.
 * With one: the mode goes to +0x58, the destination Vec3 (the vararg) to +0x24, the tuning
 * constants at data_02041dc8 to +0x18, the curve at +0x30 is primed by func_0202ed60 from
 * data_02042258 and whatever varargs follow the Vec3, the progress fields (+0x48/+0x54/+0x5c/
 * +0x60) are zeroed, and the owner is put in state 1.
 *
 * NONMATCHING: 156/156 bytes, byte-exact everywhere except ONE instruction at 0x10: the ROM
 * caches the mode straight out of its argument register (`mov r5,r1`), mwcc reads it back from
 * the block the variadic prologue just spilled (`ldr r5,[sp,#0x14]`). Same value, same slot,
 * same schedule position -- mwcc simply treats the spilled copy as canonical because va_start
 * takes the parameter's address.
 *
 * ⚠ BLOCKS a 4-member family (ov221/222/223/224 et al) -- dedupprop will not propagate from a
 * nonmatching rep.
 *
 * Three knobs ARE solved here and must be kept if you retry -- do not re-derive them:
 * 1. va_start must be `(char *)(&(last) + 1)`, NOT `(char *)&(last) + sizeof(last)`. The latter
 *    materialises &mode and adds 4 separately (`add r0,sp,#0x14 ; add ip,r0,#4`, +4 B) where the
 *    ROM folds it to one `add r0,sp,#0x18`.
 * 2. The `m = mode` local is what earns r5 and makes the prologue push {r3,r4,r5,lr}. Using the
 *    parameter directly gives push {r4,lr} and a 4-byte-larger frame, which shifts every va_list
 *    offset.
 * 3. Anchoring the va_list on `ctx` instead (same address, avoids taking &mode) does NOT help --
 *    it spills ctx and costs 40 bytes. Tried. */

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

#define va_start(ap, last) ((ap) = (char *)(&(last) + 1))
#define va_arg(ap, type)   (*(type *)(((ap) += sizeof(type)) - sizeof(type)))

extern int func_ov107_020cab14(int owner, int kind);
extern void func_0202ed60(Vec3 *curve, const Vec3 *src, char *ap);
extern Vec3 data_02041dc8;
extern Vec3 data_02042258;

void func_ov221_020d43a0(int *ctx, int mode, ...) {
    int m;
    char *ap;

    m = mode;
    ctx[0x10] = func_ov107_020cab14(ctx[0], 0);
    if (ctx[0x10] == 0) {
        return;
    }
    ctx[0x16] = m;
    ctx[0x17] = 0;

    va_start(ap, mode);
    *(Vec3 *)((char *)ctx + 0x24) = va_arg(ap, Vec3);
    *(Vec3 *)((char *)ctx + 0x18) = data_02041dc8;
    ctx[0x18] = 0;
    func_0202ed60((Vec3 *)((char *)ctx + 0x30), &data_02042258, ap);

    ctx[0x15] = 0;
    ctx[0x12] = 0;
    *(unsigned char *)(ctx[0] + 0x1c7) = 1;
}
