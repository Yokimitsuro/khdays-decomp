/* Republishes the attached pose.
 *
 * ov122 pose sync: drop the pending node-slot task (unless the actor is in
 * action state 6) and republish the Bip01 bone transform into both pose
 * handles, then let the ov107 actor base finish the frame.
 *
 * The bone record is the 0x30-byte entry func_0203bee8 allocates per bone
 * name; its +0x04 block is 44 bytes wide and is copied wholesale, which is
 * why mwcc emits the ldm/stm 4+4+3 sequence rather than field stores.
 *
 * CODEGEN NOTE -- the copy must be written as a struct-FIELD assignment
 * between typed pointers.  With raw `*(T *)(addr)` casts mwcc swaps the roles
 * of ip and lr (ip walks the source instead of the destination); giving each
 * side a real struct type with the block as a named field pins ip to the
 * destination the way the ROM has it. */
struct Ov122BoneXform {
    int w[11];
};

struct Ov122PoseNode {
    char pad00[0x10];
    struct Ov122BoneXform xform;
};

struct Ov122BoneRec {
    int tag;
    struct Ov122BoneXform xform;
};

extern void func_0203c650();
extern void func_ov107_020c7ca4();

void func_ov122_020d00b4(int self)
{
    if (*(signed char *)(self + 0x1c6) != 6 &&
        *(int *)(*(int *)(self + 0x3a4) + 0xc) != 0) {
        func_0203c650(*(int *)(self + 0x3c),
                      *(int *)(*(int *)(self + 0x3a4) + 0xc));
        *(int *)(*(int *)(self + 0x3a4) + 0xc) = 0;
    }

    (**(struct Ov122PoseNode ***)(self + 0x388))->xform =
        (*(struct Ov122BoneRec **)(self + 0x39c))->xform;

    (*(struct Ov122PoseNode **)(self + 0x38c))->xform =
        (*(struct Ov122BoneRec **)(self + 0x39c))->xform;

    func_ov107_020c7ca4(self);
}
