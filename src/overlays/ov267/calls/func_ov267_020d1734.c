/*
 * func_ov267_020d1734 -- x3 (ov212/266/267). Area attack: for each collision candidate around
 * targetPos, spawn a hit and a directed effect.
 * Get the candidate node list (020c8eb8). For each not already flagged (bit 1<<node[2] in self+0x5b):
 * dir = target - node(+0x74); unit = normalise(dir) (keeps the length); flatten dir.y=0 and
 * re-normalise, falling back to the const vec data_02042258 if degenerate; scale dir by the mode
 * (1 -> 0xc00, 2 -> 0x1000) with dir.y = 0x800. Try to spawn the hit (020ca918); on success, restore
 * unit's length, offset it by targetPos, emit the effect (020c0b90, vec by value) and set the flag.
 * If anything spawned, fire the follow-up: mode 2 -> 0x4e, else 0x51 (020c5af8).
 * Codegen: the mode dispatch and the follow-up are switches; the hit mode is a byte in 020ca918's
 * prototype (the `& 0xff` is hoisted to a stack slot); count is declared before spawned, i starts
 * at 0 before the count test and the flag is set before spawned.
 */
struct vec { int x, y, z; };
extern int  func_ov107_020c8eb8(int obj, int kind, int *list);
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  func_01ff8d18(void *a, void *b);
extern void func_01ffa724(int scale, void *in, void *out);
extern int  func_ov107_020ca918(int node, int a, int b, unsigned char mode, void *pt, int z);
extern void VEC_Add(void *a, void *b, void *c);
extern void func_ov107_020c0b90(int a, int b, struct vec v, int c);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern int  data_02042258;

void func_ov267_020d1734(int *self, int mode, int *targetPos) {
    int nodes[4];
    struct vec dir;
    struct vec unit;
    struct vec fallback;
    int count;
    int spawned = 0;
    int i;

    count = func_ov107_020c8eb8(*self, (int)targetPos, nodes);
    i = 0;
    if (count > 0) {
        fallback = *(struct vec *)&data_02042258;
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
                if (func_ov107_020ca918(nodes[i], *self, *self, mode, &dir, 0) != 0) {
                    func_01ffa724(len, &unit, &unit);
                    VEC_Add(&unit, targetPos, &unit);
                    func_ov107_020c0b90(*self, 3, unit, 0);
                    *(unsigned char *)((int)self + 0x5b) |= bit;
                    spawned = 1;
                }
            }
            i++;
        } while (i < count);
    }
    if (!spawned) {
        return;
    }
    switch (mode) {
    case 2:
        func_ov107_020c5af8(*self, 0, 0x4e, self[2]);
        break;
    default:
        func_ov107_020c5af8(*self, 0, 0x51, self[2]);
        break;
    }
}
