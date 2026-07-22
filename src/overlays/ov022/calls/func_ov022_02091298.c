/* Publish a group update: hand the group and peer to func_ov022_02090c04, then walk the
 * group's parts (0x1c8 apart, count at +0x19) and publish each one with the peer's index,
 * the caller's buffer and its slot number.
 *
 * Two things were wrong in the park, and neither was the "param-spill tie" it was filed as:
 *   - the slot argument of func_ov022_02090c7c is an int, not an unsigned char; the cast
 *     added an lsls/lsrs truncation the original does not have;
 *   - the fields have to be reached through a struct. With `*(unsigned char *)(g + 0x19)` and
 *     friends, mwcc strength-reduces the invariant addresses out of the loop and spills them,
 *     growing the frame from 8 to 0xc bytes; through `g->bCount` it re-derives them with
 *     immediate offsets, exactly like the original. Same lesson as func_ov048_020b4050. */
struct Group {
    char _pad0[0xc];
    int pParts;
    char _pad1[0x19 - 0x10];
    unsigned char bCount;
};
struct Peer {
    char _pad0[9];
    unsigned char bIndex;
};
extern void func_ov022_02090c04(struct Group *g, struct Peer *p, unsigned short *a2, int a3, int a4);
extern void func_ov022_02090c7c(int part, int idx, unsigned int *out, int slot);

void func_ov022_02091298(struct Group *g, struct Peer *p, unsigned int *out,
                         unsigned short *desc, int a4, int a5) {
    int i;
    func_ov022_02090c04(g, p, desc, a4, a5);
    i = 0;
    if ((int)g->bCount > 0) {
        int off = 0;
        do {
            func_ov022_02090c7c(g->pParts + off, p->bIndex, out, i);
            off = off + 0x1c8;
            i = i + 1;
        } while (i < g->bCount);
    }
}
