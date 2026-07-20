/* Release the actor's held handle when its state calls for it, then push the pose
 * down the node chain.  Small sibling of Ov*_ReleaseByStateAndSyncSrt.
 *
 * PARKED, and two separate things were wrong -- one of them a crack worth keeping.
 *
 * 1. func_0203c650 takes (owner, handle), not (handle).  Same dropped argument that
 *    was holding up the 312 B and 300 B siblings.
 *
 * 2. The 44-byte pose copies came out with mwcc's ldm/stm register roles INVERTED
 *    against the ROM: the ROM puts the source in lr and the destination in ip, we
 *    produced the opposite.  An earlier park on this shape concluded that "no C
 *    reordering flips mwcc's inline-block-move register roles", and that is true --
 *    reordering does not.  The POINTER TYPE does.
 *
 *        *(Pose *)(*(int *)*(int **)(obj + 0x38c) + 0x10)   <- roles inverted
 *        *(Pose *)(**(char ***)(obj + 0x38c) + 0x10)        <- ROM's roles
 *
 *    Same address, same semantics, and the only difference is whether the chain is
 *    spelled through int * or char **.  Byte arithmetic on char ** is evidently what
 *    lets mwcc settle the two block-move pointers in the ROM's order.  Worth trying
 *    first on any remaining ldm/stm role mismatch.
 */
typedef struct { int w[11]; } Pose;

extern void func_0203c650(int owner, int handle);
extern void func_ov107_020c7ca4(char *obj);

void func_ov136_020d1ea8(char *obj) {
    if ((*(unsigned char *)(obj + 0x1c4) & 0xa) != 0) {
        if (*(int *)(*(int *)(obj + 0x3a4) + 0x14) != 0) {
            func_0203c650(*(int *)(obj + 0x3c), *(int *)(*(int *)(obj + 0x3a4) + 0x14));
            *(int *)(*(int *)(obj + 0x3a4) + 0x14) = 0;
        }
        if (*(signed char *)(obj + 0x100 + 0xc7) == -1) {
            int m = *(signed char *)(obj + 0x100 + 0xc6);
            if (m != 0 && m != 1 && m != 3 && m != 5 && m != 9) {
                *(char *)(obj + 0x1c7) = 5;
            }
        }
    }
    if (*(signed char *)(obj + 0x100 + 0xc6) != 8 &&
        *(int *)(*(int *)(obj + 0x3a4) + 0x14) != 0) {
        func_0203c650(*(int *)(obj + 0x3c), *(int *)(*(int *)(obj + 0x3a4) + 0x14));
        *(int *)(*(int *)(obj + 0x3a4) + 0x14) = 0;
    }
    *(Pose *)(**(char ***)(obj + 0x38c) + 0x10) = *(Pose *)(*(char **)(obj + 0x394) + 4);
    *(Pose *)(*(char **)(obj + 0x390) + 0x10) = *(Pose *)(*(char **)(obj + 0x394) + 4);
    func_ov107_020c7ca4(obj);
}
