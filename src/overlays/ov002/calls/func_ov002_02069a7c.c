/* Does the party entry for this roster slot have ground under it?
 *
 * The signed halfword at entry+0x66 is the collision handle; a negative value means the entry has
 * none, so the answer is no. Otherwise a ray is cast from the entry's vector raised by 0x1000,
 * straight down by 0x32000, filtered by the mask at entry+0x20, and the answer is whether it hit.
 * func_0202c268 wraps the collision ray cast.
 *
 * func_ov002_020692a8 calls this per slot and only refills that slot's defaults through
 * func_ov002_02069b14 when it answers yes.
 *
 * Codegen notes. The answer is a materialised bool: set to 1 up front, cleared on both failure
 * paths, one shared exit. Writing either failure as an early return costs four bytes because mwcc
 * predicates it inline instead of branching. The failure block is written LAST, as the else of a
 * positive test, so it lands out of line the way the ROM has it. The two stack vectors are laid
 * out start-above-direction, which is this declaration order, and the direction's z component is
 * assigned before its x.
 *
 * Ghidra carries this as Ov002_TestRosterSlotGroundRay over Vec3 and Ov022Ent.
 */

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

extern int func_01fffde0(int index);
extern Vec3 *func_ov022_020881f8(int index);
extern int func_0202c268(unsigned short handle, Vec3 *from, Vec3 *dir, int mask);

int func_ov002_02069a7c(int index) {
    Vec3 from;
    Vec3 dir;
    int hit = 1;
    short handle = *(short *)(func_01fffde0(index) + 0x66);

    if (handle >= 0) {
        Vec3 *entryVec = func_ov022_020881f8(index);
        int entry = func_01fffde0(index);

        from.x = entryVec->x;
        from.y = entryVec->y + 0x1000;
        from.z = entryVec->z;
        dir.z = 0;
        dir.x = 0;
        dir.y = -0x32000;
        if (func_0202c268((unsigned short)handle, &from, &dir,
                          *(int *)(entry + 0x20)) == 0) {
            hit = 0;
        }
    } else {
        hit = 0;
    }
    return hit;
}
