/* func_ov267_020d5468 -- push one entry into the ring buffer at ctx[0]+0x90 and advance the write
 * index with a wrap.
 *
 * One of a 3-member shape family; the twins live in ov212/ov266 and are byte-identical modulo
 * relocs (matched here, fanned out with dedupprop).
 *
 * Entries are 0x38 bytes. The slot gets a fixed 0x1000 / 0x800 header, the caller's quaternion at
 * +8 and the caller's vector at +0x2c. The index at ctx[1] then advances modulo the capacity at
 * ctx[0]+0x8c -- a plain ring buffer.
 *
 * ★ The wrap is why this looked wrong at first: the ROM does `bl func_02020400` and then
 * `str r1, [r4, #4]`, storing a register the call should have clobbered. func_02020400 is the
 * divide helper and returns BOTH results -- quotient in r0, remainder in r1 -- so it must be
 * declared `long long` and the remainder taken as the HIGH word. `(int)(q >> 32)` is the modulo;
 * `(int)q` would be the quotient. (The tree already had this: see func_ov003_0204d1c0.) */

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    int x;
    int y;
    int z;
    int w;
} Quaternion;

extern long long func_02020400(int num, int den);

void func_ov267_020d5468(int *ctx, const VecFx32 *v, const Quaternion *q) {
    int i;
    int base;
    int slot;

    i = ctx[1];
    base = *(int *)(ctx[0] + 0x90);
    slot = base + i * 0x38;
    *(int *)(base + i * 0x38) = 0x1000;
    *(int *)(slot + 4) = 0x800;
    *(VecFx32 *)(slot + 0x2c) = *v;
    *(Quaternion *)(slot + 8) = *q;
    ctx[1] = (int)(func_02020400(ctx[1] + 1, *(int *)(ctx[0] + 0x8c)) >> 32);
}
