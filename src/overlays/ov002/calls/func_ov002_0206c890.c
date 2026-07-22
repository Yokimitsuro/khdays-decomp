/* func_ov002_0206c890 -- collect the world position of every live actor that belongs to the
 * current party member; returns how many were written.
 * Walks all 0x40 object slots, keeps the ones whose class byte (+0x10) maps to the same kind as
 * the active member, and appends each one's Vec3 from its own vtable getter (+0x2c of *(obj+8)).
 *
 * Parked as "class A -- register permutation": the ROM colours count->r6 and i->r5 and mwcc the
 * other way round, with four declaration orders already ruled out. Two separate things were wrong
 * and the declaration order only pays once the first is fixed:
 *  - the two leading calls are CHAINED. func_ov022_02088474 was declared `(void)` and is defined
 *    with one parameter, and the ROM's `bl ; bl` back to back with nothing in between is it being
 *    called on func_01fffe14's return value. Written as two statements, mwcc has a free slot before
 *    the calls and sinks the counter's zero into it, which is what shifts everything.
 *  - with that fixed, the declaration order below (i, count, kind, obj) is the one that colours
 *    count->r6 and i->r5. tools/declperm.py finds it by brute force; 4 of the 24 orders match.
 * The ROM's `mov r5,r6` is just mwcc reusing the counter's zero for the loop index, not an
 * artefact to reproduce by hand.
 */
extern int func_ov002_0207285c(int slot);
extern int func_01fffe14(void);
extern int func_ov022_02088474(int a);
extern char *func_ov002_02076850(int index);

typedef struct { int x, y, z; } Ov002Vec3;

/* Collects the world position of every live actor that belongs to the current party member.
 * Returns how many were written. */
int func_ov002_0206c890(char *out) {
    int i;
    int count;
    int kind;
    char *obj;
    kind = func_ov022_02088474(func_01fffe14()) & 0xff;
    count = 0;
    for (i = 0; i < 0x40; i++) {
        obj = func_ov002_02076850(i);
        if (obj != 0 && kind == func_ov002_0207285c((unsigned char)obj[0x10])) {
            *(Ov002Vec3 *)out =
                *(*(Ov002Vec3 *(**)(void *))(*(char **)(obj + 8) + 0x2c))(obj);
            out += 0xc;
            count++;
        }
    }
    return count;
}

