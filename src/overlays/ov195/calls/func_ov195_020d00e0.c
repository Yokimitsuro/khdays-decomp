/* Release the actor's held handle when its state calls for it, then publish the pose.
 *
 * Fourth variant of the Ov*_ReleaseByState shape, over a control block at +0x3d4 with the
 * handle at its +0x14, and a five-value state whitelist {0, 1, 3, 5, 9} requesting state 5.
 * Matched first try by applying what the three earlier variants cost a session each:
 *  - func_0203c650 takes (owner, handle), and the handle is the field being cleared;
 *  - the pose copies are plain struct assignments through char ** chains, which is what
 *    gives the ROM's ldm/stm register roles (int * chains invert them);
 *  - a whitelist of three or more values needs no care, unlike a two-value guard, which
 *    mwcc folds into an unsigned range test.
 */
typedef struct { int w[11]; } Pose;

extern void func_0203c650(int owner, int handle);
extern void func_ov107_020c7ca4(char *actor);

void func_ov195_020d00e0(char *actor) {
    int state;

    if ((*(unsigned char *)(actor + 0x1c4) & 0xa) != 0) {
        if (*(int *)(*(char **)(actor + 0x3d4) + 0x14) != 0) {
            func_0203c650(*(int *)(actor + 0x3c),
                          *(int *)(*(char **)(actor + 0x3d4) + 0x14));
            *(int *)(*(char **)(actor + 0x3d4) + 0x14) = 0;
        }
        if (*(signed char *)(actor + 0x1c7) == -1) {
            state = *(signed char *)(actor + 0x1c6);
            if (state != 0 && state != 1 && state != 3 && state != 5 && state != 9) {
                *(signed char *)(actor + 0x1c7) = 5;
            }
        }
    }

    if (*(signed char *)(actor + 0x1c6) != 8 &&
        *(int *)(*(char **)(actor + 0x3d4) + 0x14) != 0) {
        func_0203c650(*(int *)(actor + 0x3c),
                      *(int *)(*(char **)(actor + 0x3d4) + 0x14));
        *(int *)(*(char **)(actor + 0x3d4) + 0x14) = 0;
    }

    *(Pose *)(**(char ***)(actor + 0x38c) + 0x10) = *(Pose *)(*(char **)(actor + 0x394) + 4);
    *(Pose *)(*(char **)(actor + 0x390) + 0x10) = *(Pose *)(*(char **)(actor + 0x394) + 4);

    func_ov107_020c7ca4(actor);
}
