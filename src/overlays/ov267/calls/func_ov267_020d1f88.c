/* Reset the actor's per-frame pose cache (x3: ov212/266/267). For each of the 16
 * tracked bones: clear bit 1 of its flags word and reset its matrix slot to the
 * owner's identity/base matrix at +0xa0. Then seed the aim point from the current
 * target (+0x5a8 -> +0x190), zero the timers at +0x57c / +0x5b0 / +0x5d8, latch
 * +0x5ac from the value just zeroed, and hand off to 020d1a94.
 *
 * The `mats[i]` array field is load-bearing: 0x3cc is NOT a multiple of the 16-byte
 * element, so the combined-index trick (`base[i + K]`) cannot express it, and a raw
 * `*(T *)(base + i*16 + 0x3cc)` makes mwcc strength-reduce into a second byte-offset
 * induction variable (+8 B, and an extra register in the push list). Declaring the
 * array as a struct member reproduces the ROM's two-add form (`add r1,r0,ip,lsl #4`
 * then `add r4,r1,#0x3cc`). */
struct vec3 { int x, y, z; };
struct blk16 { int a, b, c, d; };
struct Ctx { char pad[0x3cc]; struct blk16 mats[16]; };

extern void func_ov267_020d56ac(int a);

void func_ov267_020d1f88(int *self) {
    int i = 0;

    for (; i < 0x10; i++) {
        *(int *)(((int *)*self)[i + 0xe3] + 0x5c) &= ~2;
        ((struct Ctx *)*self)->mats[i] = *(struct blk16 *)(*self + 0xa0);
    }
    *(struct vec3 *)(*self + 0x4f0) = *(struct vec3 *)(*(int *)(*self + 0x5a8) + 0x190);
    *(int *)(*self + 0x57c) = 0;
    *(int *)(*self + 0x5b0) = 0;
    *(int *)(*self + 0x5ac) = *(int *)(*self + 0x5b0);
    *(int *)(*self + 0x5d8) = 0;
    func_ov267_020d56ac(*(int *)(*self + 0x5d4));
}
