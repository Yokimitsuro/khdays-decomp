/* func_ov181_020cd1e0 -- head of a 10-member family (ov181..ov183 and company).
 *
 * FULL SEMANTICS: ask the manager for the current target (func_ov107_020cab14, which
 * returns the node and writes the SQUARED distance to its stack out-parameter).  With no
 * target, set mode 2 in the owner's byte at 0x1c7 and end the state with no successor.
 * With one: subtract both radii (field 0x80 of target and of owner) from the square root
 * of the distance, set the timer at +0x20 to `field_0x2c * 30 / 20`, take the bearing to
 * the target with VEC_Subtract + func_020050b4, interpolate the orientation (func_0202f384
 * + func_01ffa724 at weight 0x100) and, if the lock byte at +0xc is free, re-aim the owner
 * (mode 3) and chain func_ov181_020cd300.
 *
 * TIE: TWO BYTES.  The ROM holds `target` in r7 and `owner` in r6; mwcc assigns them the
 * other way round.  Instruction for instruction identical otherwise.
 *
 * Axes exhausted 2026-07-19:
 *   - 120 permutations of the declaration order (all 5 locals): all identical.  The
 *     "declaration order = register order" crack does NOT apply here.
 *   - guard spellings: `target == 0` vs `s[4] == 0`; target defined before or after the
 *     guard; the store as `s[4] = (int)(target = ...)`.  This DID come down from 5 bytes
 *     to 2 -- the good form is `s[4] = (int)func(...); target = (int *)s[4];`.
 *   - dropping `owner` (costs 14 bytes), dropping `target`, putting both in an `inline`
 *     helper (77 bytes: the helper changes the whole evaluation order).
 *   - merging `dist` and the Vec3 into one stack struct: still 2 bytes.
 *   - 12 type combinations (int, char, void and unsigned pointers for each).
 *   - ALL 27 COMPILERS (tools/allcc.py): every 2.0/3.0 and the dsi builds up to 1.3p1 give
 *     EXACTLY 2; the dsi 1.6 builds give 10.  None is right.
 *
 * Added 2026-07-20, from applying the day's cracks to the 344 B sibling func_ov181_020cd300
 * (same r6/r7 tie, 37 differing lines, unmoved by all of these):
 *   - the split `field = f(...); local = field;` read-back that cracked func_ov141_020cce98;
 *   - assigning `owner` BEFORE the call instead of after the guard (48 lines, worse);
 *   - converting the locals to POINTER type with array indexing, i.e. the exact shape of
 *     func_ov141_020cce98, which matches and has this same one-use/two-use pattern.
 *   That last one is the interesting negative: the shape that matches in the small function
 *   does not carry to the large one, so whatever picks r6/r7 is not the spelling of these
 *   two locals.
 *
 * The open hypothesis is still worth testing: what decides mwcc between r6 and r7 for two
 * locals live at once when definition order does not.  Here `owner` has 1 use and `target`
 * 2, and the ROM gives the LOW register to the one with FEWER uses -- the opposite of our
 * build.  Confirm that on another function and it is a new rule that unblocks this family.
 *
 * NOTE: this file did not COMPILE between 2026-07-19 and 2026-07-20.  The type-combination
 * line above listed pointer types separated by slashes, and an "int-star-slash" sequence
 * accidentally spelled a comment terminator, closing this block early and leaving the Vec3
 * typedef below to be parsed as code.  A parked file that does not compile cannot be
 * re-tested, which defeats the whole point of parking it with a write-up.  Verify a park
 * still builds before committing it -- and mind that hazard when writing ABOUT pointer
 * types inside a block comment, which is exactly how this note first reintroduced it.
 */
typedef struct { int x, y, z; } Vec3;

extern int *func_ov107_020cab14(int owner, int *distOut);
extern void func_0203c634(int *self, int action, void *cb);
extern int FX_Sqrt(int x);
extern void VEC_Subtract(void *a, void *b, Vec3 *dst);
extern int func_020050b4(int x, int z);
extern void func_0202f384(void *dst, int src, void *tbl);
extern void func_01ffa724(int t, void *a, void *b);
extern void func_ov107_020c9264(int owner, int mode, int arg);
extern void func_ov181_020cd300(void);
extern int data_02042258;

void func_ov181_020cd1e0(int *self) {
    int dist;
    Vec3 v;
    int *s = (int *)self[1];
    int *target;
    int *owner;

    s[4] = (int)func_ov107_020cab14(*s, &dist);
    target = (int *)s[4];
    if (target == 0) {
        *(char *)(*s + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)((char *)self + 0x20), 0);
        return;
    }
    owner = (int *)*s;
    dist = FX_Sqrt(dist) - (owner[0x20] + target[0x20]);
    s[8] = *(int *)(*self + 0x2c) * 0x1e / 20;
    VEC_Subtract((char *)s[4] + 0x190, (void *)s[1], &v);
    s[6] = func_020050b4(v.x, v.z);
    func_0202f384((char *)s + 0x54, *s + 0xa0, &data_02042258);
    func_01ffa724(0x100, (char *)s + 0x54, (char *)s + 0x54);
    if (*(unsigned char *)s[3] != 0) {
        return;
    }
    func_ov107_020c9264(*s, 3, 1);
    func_0203c634(self, *(signed char *)((char *)self + 0x20), (void *)&func_ov181_020cd300);
}
