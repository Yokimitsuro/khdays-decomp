/* Tick handler of the ov274 enemy. The 44-byte placements of the +0x3c8 bone (+4) are copied
 * into the +0x3ac pool node's and the +0x3c4 frame's poses (+0x10), the +0x3cc bone's into the
 * +0x3bc frame, the +0x3d0 bone's into +0x3c0, the +0x3d4 bone's into +0x3b8 and back from the
 * +0x3b0 pool node into the +0x3d4 bone. Outside sub-states 6 and 8 the +0x3e0 block's +0x14
 * effect is released, outside 5 its +4 effect; if flagged (+0x1c4 & 0xa) outside sub-states
 * 0, 1, 3, 2 and 0xc sub-state 2 is forced and that +4 effect released too. Then the base tick runs.
 * The copies write their DESTINATION as a struct field through a typed pointer. */
typedef struct { int w[11]; } Placement;
typedef struct { int pad; Placement placement; } Bone;              /* +4 */
typedef struct { char pad[0x10]; Placement placement; } Frame;      /* +0x10 */

extern void func_0203c650(int list, int node);
extern void func_ov107_020c7ca4(int self);

void func_ov206_020cc9b4(int self)
{
    {
        Frame *node = *(Frame **)*(int *)(self + 0x3ac);
        Bone *bone = *(Bone **)(self + 0x3c8);
        node->placement = bone->placement;
    }
    {
        Frame *frame = *(Frame **)(self + 0x3c4);
        Bone *bone = *(Bone **)(self + 0x3c8);
        frame->placement = bone->placement;
    }
    {
        Frame *frame = *(Frame **)(self + 0x3bc);
        Bone *bone = *(Bone **)(self + 0x3cc);
        frame->placement = bone->placement;
    }
    {
        Frame *frame = *(Frame **)(self + 0x3c0);
        Bone *bone = *(Bone **)(self + 0x3d0);
        frame->placement = bone->placement;
    }
    {
        Frame *frame = *(Frame **)(self + 0x3b8);
        Bone *bone = *(Bone **)(self + 0x3d4);
        frame->placement = bone->placement;
    }
    {
        Frame *node = *(Frame **)*(int *)(self + 0x3b0);
        Bone *bone = *(Bone **)(self + 0x3d4);
        node->placement = bone->placement;
    }
    if (*(signed char *)(self + 0x100 + 0xc6) != 8 && *(signed char *)(self + 0x100 + 0xc6) != 6
        && *(int *)(*(int *)(self + 0x3e0) + 0x14) != 0) {
        func_0203c650(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x3e0) + 0x14));
        *(int *)(*(int *)(self + 0x3e0) + 0x14) = 0;
    }
    if (*(signed char *)(self + 0x100 + 0xc6) != 5 && *(int *)(*(int *)(self + 0x3e0) + 4) != 0) {
        func_0203c650(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x3e0) + 4));
        *(int *)(*(int *)(self + 0x3e0) + 4) = 0;
    }
    if ((*(unsigned char *)(self + 0x1c4) & 0xa) != 0
        && *(signed char *)(self + 0x100 + 0xc6) != 0 && *(signed char *)(self + 0x100 + 0xc6) != 1
        && *(signed char *)(self + 0x100 + 0xc6) != 3 && *(signed char *)(self + 0x100 + 0xc6) != 2
        && *(signed char *)(self + 0x100 + 0xc6) != 0xc) {
        *(unsigned char *)(self + 0x1c7) = 2;
        if (*(int *)(*(int *)(self + 0x3e0) + 4) != 0) {
            func_0203c650(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x3e0) + 4));
            *(int *)(*(int *)(self + 0x3e0) + 4) = 0;
        }
    }
    func_ov107_020c7ca4(self);
}
