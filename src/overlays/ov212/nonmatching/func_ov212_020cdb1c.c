/*
 * NONMATCHING -- 488/492 bytes, fully decoded; TWO independent residual diffs (2026-07-17):
 *   1. TAIL self[2] CSE (the 4-byte / 1-instruction size gap): the ROM loads `self[2]` (r3) TWICE
 *      -- once inside each of the two 020c5af8 call blocks -- while mwcc hoists it ONCE before the
 *      `mode==2` branch (it DOES hoist the shared `*self` and `#0`, exactly as the ROM does; only
 *      self[2] is rematerialised). This is the ctx-CSE / pool-rematerialisation tie class: the ROM
 *      re-loads where mwcc shares. A single ternary-tag call collapses the two blocks (wrong shape);
 *      the two-block form is correct and mwcc will not un-share the r3 load.
 *   2. SCALAR FRAME LAYOUT: the byte-diffs at the `str/ldr [sp,#N]` sites are pure slot assignment --
 *      ROM places len@sp+8, spawned@sp+0xc, count@sp+0x10, (mode&0xff)@sp+0x14; mwcc orders them
 *      differently. Same instruction COUNT, only the offsets differ. Not yet steered.
 * SOLVED here and worth keeping: the mode dispatch is a SWITCH (`cmp#1;beq; cmp#2;beq; b` to
 * out-of-line case bodies), not an if/else-if -- that fixed one of the original two missing insns.
 * Arities verified against the tree: 020c8eb8=3, 020ca918=6, 020c0b90=4 (arg3 vec3 BY VALUE),
 * 020c5af8=4. Attack ONLY these two residuals; everything else is byte-exact.
 *
 * func_ov212_020cdb1c -- x3 (ov212/266/267). Area attack: for each collision candidate around
 * targetPos, spawn a hit and a directed effect.
 * Get the candidate node list (020c8eb8). For each not already flagged (bit 1<<node[2] in self+0x5b):
 * dir = target - node(+0x74); unit = normalise(dir) (keeps the length); flatten dir.y=0 and
 * re-normalise, falling back to the const vec data_02042258 if degenerate; scale dir by the mode
 * (1 -> 0xc00, 2 -> 0x1000) with dir.y = 0x800. Try to spawn the hit (020ca918); on success, restore
 * unit's length, offset it by targetPos, emit the effect (020c0b90, vec by value) and set the flag.
 * If anything spawned, fire the follow-up: mode 2 -> 0x4e, else 0x51 (020c5af8).
 */
struct vec { int x, y, z; };
extern int  func_ov107_020c8eb8(int obj, int kind, int *list);
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  func_01ff8d18(void *a, void *b);
extern void func_01ffa724(int scale, void *in, void *out);
extern int  func_ov107_020ca918(int node, int a, int b, int mode, void *pt, int z);
extern void VEC_Add(void *a, void *b, void *c);
extern void func_ov107_020c0b90(int a, int b, struct vec v, int c);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern int  data_02042258;

void func_ov212_020cdb1c(int *self, int mode, int *targetPos) {
    int nodes[4];
    struct vec dir;
    struct vec unit;
    struct vec fallback;
    int spawned = 0;
    int count;
    int i;

    count = func_ov107_020c8eb8(*self, (int)targetPos, nodes);
    if (count > 0) {
        fallback = *(struct vec *)&data_02042258;
        i = 0;
        do {
            int bit = (1 << *(unsigned short *)(nodes[i] + 2)) & 0xff;
            if ((*(unsigned char *)((int)self + 0x5b) & bit) == 0) {
                int len;
                VEC_Subtract((void *)(nodes[i] + 0x74), targetPos, &dir);
                len = func_01ff8d18(&dir, &unit);
                dir.y = 0;
                if (func_01ff8d18(&dir, &dir) == 0) {
                    dir = fallback;
                }
                switch (mode) {
                case 1:
                    func_01ffa724(0xc00, &dir, &dir);
                    dir.y = 0x800;
                    break;
                case 2:
                    func_01ffa724(0x1000, &dir, &dir);
                    dir.y = 0x800;
                    break;
                }
                if (func_ov107_020ca918(nodes[i], *self, *self, mode & 0xff, &dir, 0) != 0) {
                    func_01ffa724(len, &unit, &unit);
                    VEC_Add(&unit, targetPos, &unit);
                    func_ov107_020c0b90(*self, 3, unit, 0);
                    spawned = 1;
                    *(unsigned char *)((int)self + 0x5b) |= bit;
                }
            }
            i++;
        } while (i < count);
    }
    if (!spawned) {
        return;
    }
    if (mode == 2) {
        func_ov107_020c5af8(*self, 0, 0x4e, self[2]);
        return;
    }
    func_ov107_020c5af8(*self, 0, 0x51, self[2]);
}
