/* Release the attachments the actor's current state no longer needs, then push its
 * transform down the node chain.  One of the x10 shared bodies across the enemy
 * overlays (ov166-ov177).
 *
 *  - if the actor is flagged (0x1c4 & 0xa) and has no pending state, and the current
 *    state is outside the whitelist {0, 1, 3, 0xc}, request state 0xc;
 *  - unless the state is 8, release the handle held in the control block at +0x39c
 *    and clear it;
 *  - unless the state is 9, destroy and null the two attachments at +0x3a0;
 *  - unless the state is 8, destroy and null the attachment at +0x3a8;
 *  - copy the 44-byte SRT transform from +0x394's node into +0x398's, and from there
 *    into the node behind +0x388, then run the shared ov107 update.
 *
 * PARKED as "register-naming ties only", with both residues correctly identified and
 * both wrongly attributed.  What actually differed:
 *  - the park's loop stored the null OUTSIDE the emptiness test.  The ROM's `beq`
 *    skips the call AND the store, so the store belongs inside.  Writing it outside is
 *    a different function, and it is what moved the scratch registers the note blamed.
 *  - the park indexed the attachment pair as `((int *)this)[0xe8 + i]`, folding the
 *    base into the index.  `((void **)(actor + 0x3a0))[i]` keeps the ROM's shape.
 *  - the 44-byte copies need no trick at all: a plain struct assignment through two
 *    casts gives the ROM's ldm/stm register roles.  The park's intermediate `pd`
 *    pointers are what inverted them.
 *
 * The note said "no C reordering flips mwcc's inline-block-move register roles", which
 * was true of the forms it tried and false of the function.
 */
typedef struct { int w[11]; } SrtTransform;   /* 44 bytes, the node's SRT block */

extern void func_0203c650(int owner, int handle);
extern void func_ov107_020cb100(void *attachment);
extern void func_ov107_020c7ca4(void *actor);

void func_ov176_020d0264(char *actor) {
    int i;
    int state;

    if ((*(unsigned char *)(actor + 0x1c4) & 0xa) != 0 &&
        *(signed char *)(actor + 0x1c7) == -1) {
        state = *(signed char *)(actor + 0x1c6);
        if (state != 0 && state != 1 && state != 3 && state != 0xc) {
            *(signed char *)(actor + 0x1c7) = 0xc;
        }
    }

    if (*(signed char *)(actor + 0x1c6) != 8 && *(int *)(*(char **)(actor + 0x39c) + 4) != 0) {
        func_0203c650(*(int *)(actor + 0x3c), *(int *)(*(char **)(actor + 0x39c) + 4));
        *(int *)(*(char **)(actor + 0x39c) + 4) = 0;
    }

    if (*(signed char *)(actor + 0x1c6) != 9) {
        for (i = 0; i < 2; i++) {
            if (((void **)(actor + 0x3a0))[i] != 0) {
                func_ov107_020cb100(((void **)(actor + 0x3a0))[i]);
                ((void **)(actor + 0x3a0))[i] = 0;
            }
        }
    }

    if (*(signed char *)(actor + 0x1c6) != 8 && *(void **)(actor + 0x3a8) != 0) {
        func_ov107_020cb100(*(void **)(actor + 0x3a8));
        *(void **)(actor + 0x3a8) = 0;
    }

    *(SrtTransform *)(*(char **)(actor + 0x398) + 0x10) =
        *(SrtTransform *)(*(char **)(actor + 0x394) + 4);
    *(SrtTransform *)(**(char ***)(actor + 0x388) + 0x10) =
        *(SrtTransform *)(*(char **)(actor + 0x398) + 0x10);

    func_ov107_020c7ca4(actor);
}
