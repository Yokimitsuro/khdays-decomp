/* NONMATCHING (count=6, 228/228 B) -- ONE instruction out of place: the ROM issues
 * `bic lr, lr, #0xff00` late (right before the final orr), mwcc issues it early
 * (after the first lsl of the extract chain). Everything else is byte-exact.
 *
 * ★ WHAT THIS FILE NOW SETTLES: the +0x60 "hw60" config half-word is a BITFIELD, and
 * the whole shift soup previous versions transcribed by hand is mwcc's canonical
 * bitfield read-modify-write of an `unsigned short hi : 8` at offset 8:
 *     lsl #16 ; lsr #24        <- read a width-8 field at offset 8 (32-8-8, 32-8)
 *     bic #0x40                <- &= ~0x40
 *     lsl #16 ; lsr #16        <- the intermediate is unsigned short (the field's type)
 *     bic lr, #0xff00          <- clear the field in the container
 *     lsl #24 ; orr lr, r3 lsr #16   <- re-insert at offset 8
 * `((struct NodeCfg *)(node + 0x60))->hi &= ~0x40;` emits ALL of that, byte-identical
 * to the hand-written shifts -- so the old transcription was equivalent, just
 * unreadable. Use the struct. This retires the "hw60 is a mystery" class: any other
 * hw60 site should be spelled as a bitfield first, and where the scheduler does not
 * bite it will simply match.
 *
 * RULED OUT for the bic placement (all 228 B, all the same 5-instruction shift):
 *   - `&=` vs `x = x & ~0x40` vs a temp vs a cast to unsigned short vs a pointer local;
 *   - all 6 orders of the three tail statements (the current order is the best at 5);
 *   - a 32-bit container (`unsigned int lo:8, hi:8`) -> 220 B, wrong;
 *   - `volatile` container -> 232 B, wrong (adds a reload).
 * The emission order naturally puts that bic late, so mwcc is HOISTING it here and the
 * ROM's build did not. That is the whole remaining question.
 *
 * The 64-bit fixed-point scale MATCHED and is settled: `holder->0x7c -= (int)((((long
 * long)m << 7) + 0x800) >> 12)` with m = (*this)->0x2c * 0x1e reproduces the
 * mul/asr/adds/adc/lsr/orr lowering exactly (this un-deferred the fixed-point class).
 *
 * Semantics: copy the Vec3 at holder+0x78 to holder+0x54; drain holder->0x7c by the
 * scaled step; bail unless node->0x17a bit0 is set; notify (0x12), clear the node's
 * 0x40 config bit, zero holder->0x6c, clear bit 1 of holder->0x51, and advance to
 * func_ov181_020ce748. */
extern int func_ov107_020c9264();
extern int func_ov107_020c9ee8();
extern int func_0203c634();
extern int func_ov181_020ce748();

struct Vec3 { int x, y, z; };
struct NodeCfg { unsigned short lo : 8, hi : 8; };
struct NodeBits { unsigned char ready : 1; };

void func_ov181_020ce664(int this_) {
    int holder = *(int *)(this_ + 4);
    int node;
    int m;

    *(struct Vec3 *)(holder + 0x54) = *(struct Vec3 *)(holder + 0x78);

    m = *(int *)(*(int *)this_ + 0x2c) * 0x1e;
    *(int *)(holder + 0x7c) -= (int)((((long long)m << 7) + 0x800) >> 12);

    node = *(int *)holder;
    if (((struct NodeBits *)(node + 0x17a))->ready == 0) return;

    func_ov107_020c9264(node, 0x12, 0);
    func_ov107_020c9ee8(*(int *)(*(int *)holder + 0x390), 0, 0);

    node = *(int *)holder;
    ((struct NodeCfg *)(node + 0x60))->hi &= ~0x40;
    *(int *)(holder + 0x6c) = 0;
    *(unsigned char *)(holder + 0x51) &= ~2;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), func_ov181_020ce748);
}
