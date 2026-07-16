/* UNFINISHED -- NOT a proven tie. 784/784 bytes, 196/196 instructions.
 *
 * The only difference left is WHERE three stores go. The sink call takes 7 args, so w0/w1/w2 are
 * stack args at sp+0/4/8. The ROM spills each raw word to its slot the moment its last pack byte is
 * written (`strb r6,[sp,#0x17]` then `str r6,[sp]`); mwcc 3.0/139 keeps all three in registers and
 * stores them at the call site instead. Everything else -- the counts, the packing, the template
 * copy, the ldm/stm snapshot -- already matches, and the register renaming in the diff falls out of
 * those three stores.
 *
 * Ruled out, so do not repeat:
 *   - A `static inline` PackCoord helper (the project builds with -inline on,noauto, so this was
 *     the obvious shape): identical output, stores still late.
 *   - Passing the position as a by-value Vec3 5th arg on the theory that sp+0/4/8 is a 12-byte
 *     struct marshal: mwcc emits a full `ldm/stm` copy at the call and it costs 4 bytes.
 *
 * What IS solved and must be kept: the words are UNSIGNED (the ROM shifts with `lsr`, not `asr` --
 * that alone was 8 bytes); ctx[1] is loaded ONCE into a pointer and dereferenced three times, not
 * reloaded; Msg needs short members so mwcc copies the 14-byte template by halfwords like the ROM's
 * 3x2 loop plus a trailing one; and the ctx[0xd..0xf] snapshot is a struct assignment (ldm/stm).
 *
 * Next idea: this is a spill-timing difference, so look for something that raises register pressure
 * across the packs the way the ROM's allocator evidently saw it. Compare against
 * func_ov210_020d0d24 (matched) which has no stack args at all.
 */

/* func_ov210_020d114c -- ov210's move chooser with a give-up path.
 *
 * Two halves. If any of the low nibble of ctx[0]+0x1c4 is set AND a target is available, it behaves
 * like func_ov210_020d0d24: FX_Sqrt the squared distance the acquire call wrote through its
 * out-param, subtract both collision radii, and pick a move by range and a d100:
 *
 *   d <= 0x1000  -> move 15
 *   d >= 0x8000  -> move 10
 *   otherwise    -> a d100: <25 move 10, <50 move 13, <75 move 12, <99 move 11, else move 9
 *
 * With no flag or no target it takes the second half: turn the "idle" bits on (hw60 |= 0x4c,
 * +0x1ae |= 1, and bit 0 OFF on the sub-object at +0x3b0), kick animation 6, zero the two velocity
 * words, snapshot ctx[1]'s position into ctx[0xd..0xf], and then send a 14-byte message.
 *
 * The message is a template copied from data_ov210_020d46fc with three coordinates packed into it,
 * each 32-bit word squeezed into 3 bytes BIG-ENDIAN with the sign bit folded onto bit 7 of the
 * first: `hi = ((w >> 16) & 0x7f) | ((w >> 24) & 0x80)`, then bits 8-15, then bits 0-7. So each is
 * a sign plus 7 integer bits plus 16 fraction bits -- a Q16 value compressed for the wire. It goes
 * to the callback at *(ctx[0]+0x24) along with the raw words, and 0xe is sizeof(Msg).
 *
 * Struct shapes that matter (codegen-cracks.md, "model it as a struct"):
 *   - Msg must contain shorts, not just bytes: mwcc copies the 14-byte template with halfword
 *     loads/stores, which is what the ROM's 3x2-halfword loop plus a trailing one is.
 *   - The position snapshot is a struct assignment -- that is the ROM's ldmia/stmia pair.
 *
 * `+ (d - d)` on the RNG result is NOT a typo; see deferred-ties.md.
 */

typedef struct {
    unsigned short lo : 8;
    unsigned short hi : 8;
} Hw60;

typedef struct {
    unsigned f : 8;
} B8;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    short a;
    short b;
    unsigned char pad;
    unsigned char v[9];
} Msg;

typedef void (*MsgSink)(int obj, Msg *m, int size, void *sink,
                        unsigned int w0, unsigned int w1, unsigned int w2);

extern int func_ov107_020cab14(int obj, int *outDistSq);
extern void func_0203c634(int self, int slot, void (*cb)(void));
extern int FX_Sqrt(int x);
extern int func_02023eb4();
extern void func_ov107_020c9264(int obj, int anim, int flag);
extern void func_ov210_020d145c(void);
extern const Msg data_ov210_020d46fc;

void func_ov210_020d114c(int self) {
    int *ctx;
    int *owner;
    int target;
    int d;
    int roll;
    unsigned int w0, w1, w2;
    unsigned int *pos;
    unsigned short v;
    MsgSink sink;
    Msg m;

    ctx = *(int **)(self + 4);
    if ((*(unsigned char *)(ctx[0] + 0x1c4) & 0xf) != 0) {
        ctx[4] = func_ov107_020cab14(ctx[0], &d);
        target = ctx[4];
        if (target != 0) {
            owner = (int *)ctx[0];
            d = FX_Sqrt(d) - (owner[0x20] + *(int *)(target + 0x80));

            if (d <= 0x1000) {
                *(signed char *)(ctx[0] + 0x1c7) = 15;
                func_0203c634(self, *(signed char *)(self + 0x20), 0);
                return;
            }
            if (d >= 0x8000) {
                *(signed char *)(ctx[0] + 0x1c7) = 10;
                func_0203c634(self, *(signed char *)(self + 0x20), 0);
                return;
            }
            roll = func_02023eb4(0x65) + (d - d);
            if (roll < 0x19) {
                *(signed char *)(ctx[0] + 0x1c7) = 10;
                func_0203c634(self, *(signed char *)(self + 0x20), 0);
                return;
            }
            if (roll < 0x32) {
                *(signed char *)(ctx[0] + 0x1c7) = 13;
                func_0203c634(self, *(signed char *)(self + 0x20), 0);
                return;
            }
            if (roll < 0x4b) {
                *(signed char *)(ctx[0] + 0x1c7) = 12;
                func_0203c634(self, *(signed char *)(self + 0x20), 0);
                return;
            }
            if (roll < 0x63) {
                *(signed char *)(ctx[0] + 0x1c7) = 11;
                func_0203c634(self, *(signed char *)(self + 0x20), 0);
                return;
            }
            *(signed char *)(ctx[0] + 0x1c7) = 9;
            func_0203c634(self, *(signed char *)(self + 0x20), 0);
            return;
        }
    }

    v = *(unsigned short *)(ctx[0] + 0x60);
    *(unsigned short *)(ctx[0] + 0x60) =
        (unsigned short)((v & ~0xff00)
                         | (((((unsigned int)v << 0x10) >> 0x18 | 0x4c) << 0x18) >> 0x10));
    *(unsigned short *)(ctx[0] + 0x1ae) |= 1;
    ((B8 *)(*(int *)(ctx[0] + 0x3b0) + 8))->f &= ~1;
    func_ov107_020c9264(ctx[0], 6, 0);

    ctx[0xb] = 0;
    ctx[0xc] = 0;
    *(Vec3 *)&ctx[0xd] = *(Vec3 *)ctx[1];

    m = data_ov210_020d46fc;

    pos = (unsigned int *)ctx[1];

    w0 = pos[0];
    m.v[0] = (unsigned char)(((w0 >> 0x10) & 0x7f) | ((w0 >> 0x18) & 0x80));
    m.v[1] = (unsigned char)(w0 >> 8);
    m.v[2] = (unsigned char)w0;
    w1 = pos[1];
    m.v[3] = (unsigned char)(((w1 >> 0x10) & 0x7f) | ((w1 >> 0x18) & 0x80));
    m.v[4] = (unsigned char)(w1 >> 8);
    m.v[5] = (unsigned char)w1;
    w2 = pos[2];
    m.v[6] = (unsigned char)(((w2 >> 0x10) & 0x7f) | ((w2 >> 0x18) & 0x80));
    m.v[7] = (unsigned char)(w2 >> 8);
    m.v[8] = (unsigned char)w2;
    m.pad = 0;

    sink = *(MsgSink *)(ctx[0] + 0x24);
    if (sink != 0) {
        sink(ctx[0], &m, 0xe, (void *)sink, w0, w1, w2);
    }

    ctx[0x18] = 0;
    *(unsigned char *)((char *)ctx + 0x66) = 0;
    func_0203c634(self, *(signed char *)(self + 0x20), func_ov210_020d145c);
}
