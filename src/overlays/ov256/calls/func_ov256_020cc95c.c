/* Draw pre-pass of the ov256 actor: after a boost pose (move 0xe) the boost level +0x45c grows up to
 * 4. The seven armour links (+0x3d4, 0xc each) copy their source node's pose (+4) into their target
 * model (+0x30); outside move 7 the +0x4e0 effect is released from the +0x3c task list. In move 0xe
 * the armour piece lost at the current boost hides (+0x5c bit 1: 1 -> +0x3e0, 2 -> +0x3f8,
 * 3 -> +0x3ec, 4 -> +0x3d4). The +0x3f4 node's pose goes to the +0x42c model and on to the +0x428
 * shape, then the base pre-pass runs. */
typedef struct { int w[11]; } Pose;

extern void func_0203c650(void *taskList, void *handle);
extern void func_ov107_020c7ca4(char *self);

#define LINK(dst, src) (*(Pose *)(*(char **)(self + (dst)) + 0x30) = *(Pose *)(*(char **)(self + (src)) + 4))

void func_ov256_020cc95c(char *self)
{
    if (*(signed char *)(self + 0x1c6) == 0xe && *(int *)(self + 0x45c) != 4) {
        (*(int *)(self + 0x45c))++;
    }
    LINK(0x3d8, 0x3dc);
    LINK(0x3e4, 0x3e8);
    LINK(0x3f0, 0x3f4);
    LINK(0x3fc, 0x400);
    LINK(0x408, 0x40c);
    LINK(0x414, 0x418);
    LINK(0x420, 0x424);
    if (*(signed char *)(self + 0x1c6) != 7 && *(void **)(self + 0x4e0) != 0) {
        func_0203c650(*(void **)(self + 0x3c), *(void **)(self + 0x4e0));
        *(void **)(self + 0x4e0) = 0;
    }
    if (*(signed char *)(self + 0x1c6) == 0xe) {
        switch (*(int *)(self + 0x45c)) {
        case 1:
            *(int *)(*(char **)(self + 0x3e0) + 0x5c) |= 2;
            break;
        case 2:
            *(int *)(*(char **)(self + 0x3f8) + 0x5c) |= 2;
            break;
        case 3:
            *(int *)(*(char **)(self + 0x3ec) + 0x5c) |= 2;
            break;
        case 4:
            *(int *)(*(char **)(self + 0x3d4) + 0x5c) |= 2;
            break;
        }
    }
    *(Pose *)(*(char **)(self + 0x42c) + 0x10) = *(Pose *)(*(char **)(self + 0x3f4) + 4);
    *(Pose *)(**(char ***)(self + 0x428) + 0x10) = *(Pose *)(*(char **)(self + 0x42c) + 0x10);
    func_ov107_020c7ca4(self);
}
