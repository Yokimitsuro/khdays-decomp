/* func_ov117_020cd494 -- head of a 5-member family.  Try to hand off to the follow-up
 * target; if there is none, clear the retry flag and loop back to the search state.
 *
 * NONMATCHING: 256/256 bytes, FOUR INSTRUCTIONS, and they are only an ORDER.  The 4-byte
 * parameter pair is copied out of the table high-halfword-first by the ROM and
 * low-first by us; everything else in the function is byte-identical, including the
 * `add r1, sp, #0` position that a sibling park spent a session on.
 *
 *     ROM   ldrh r2,[r0,#0xa] ; ldrh r0,[r0,#8] ; strh r2,[sp,#2] ; strh r0,[sp]
 *     ours  ldrh r2,[r0,#8]   ; ldrh r0,[r0,#0xa] ; strh r2,[sp] ; strh r0,[sp,#2]
 *
 * ** THE ORDER DEPENDS ON THE SOURCE OFFSET BEING ZERO. **  Measured directly, by taking
 * func_ov123_020cce74 -- which MATCHES and emits the ROM's high-first order -- and moving
 * only the offset its copy reads from:
 *
 *     params = *(struct u16pair *)&data;          -> high-first  (matches)
 *     params = ((struct u16pair *)&data)[1];      -> low-first
 *     params = *(struct u16pair *)(data + 8);     -> low-first
 *     params = tbl.p;             (struct member) -> low-first
 *     params = pairs[2];          (array of pair) -> low-first
 *     params = *(struct u16pair *)((char *)&data + 8); -> low-first
 *
 * So mwcc 3.0/139 emits high-first ONLY at offset 0, and no spelling of a non-zero offset
 * reproduces it.  This function needs +8, and the pool word is a relocation against
 * data_ov117_020cdc28 itself, so the offset cannot be folded into a different symbol
 * without breaking the reloc.
 *
 * That is a sharper statement than the sibling parks had.  func_ov141_020cd2b0 (x7) is
 * stuck on exactly this and its note says the reversal "seems to depend on a later partial
 * overwrite" -- that theory came from func_ov131_020cdf20, which copies at offset 0 and
 * happens to have an overwrite after it.  The offset is the variable that actually tracks.
 *
 * Ruled out here, all still 9 differing lines: field-by-field assignment in both orders,
 * an index-pair assignment, a pointer local for the source, declaring the global as
 * short[] or as a scalar short, and all six permutations of the three local declarations.
 *
 * Already solved, do not redo:
 *  - the out-parameter is 16 bytes, not a Vec3; a 12-byte local leaves the frame 4 short.
 *  - the bit-0 test on +0x17a wants the `unsigned char b : 1` bitfield form (lsl/lsr),
 *    not `& 1` (which gives tst).
 *  - the hw60 high-byte clear wants the bitfield form too, per codegen-cracks.md.
 */
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Vec4;
struct bit0 { unsigned char b : 1; };
typedef struct { unsigned short a, b; } Pair;
struct hw60 { unsigned short lo : 8, hi : 8; };

extern int func_ov107_020c8eb8(int owner, int src, Vec4 *out);
extern void func_0203c634(int *self, int action, void *cb);
extern void func_ov117_020cd594(void);
extern char data_ov117_020cdc28[];

void func_ov117_020cd494(int *self) {
    int *ctx = (int *)self[1];
    Vec4 out;
    Pair p;
    void (*cb)(int owner, Pair *p, int n);

    *(Vec3 *)((char *)ctx + 0x2c) = *(Vec3 *)((char *)ctx + 0x64);

    if (func_ov107_020c8eb8(*ctx, *ctx + 0x74, &out) != 0) {
        p = *(Pair *)(data_ov117_020cdc28 + 8);
        cb = *(void (**)(int, Pair *, int))(*ctx + 0x24);
        if (cb != 0) {
            cb(*ctx, &p, 4);
        }
        ctx[0x1d] = out.w[0];
        *(signed char *)(*ctx + 0x1c7) = 7;
        func_0203c634(self, *(signed char *)((char *)self + 0x20), 0);
        return;
    }

    if (((struct bit0 *)(*ctx + 0x17a))->b == 0) {
        return;
    }
    ctx[0xe] = 0;
    ((struct hw60 *)(*ctx + 0x60))->hi &= ~6;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), &func_ov117_020cd594);
}
