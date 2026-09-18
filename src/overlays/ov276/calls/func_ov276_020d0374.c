/* Tick hook of the ov276 enemy: a hit-flagged actor (+0x1c4 bits 1/3) idling in sub-state 6
 * requests sub-state 2; outside sub-state 6 the +0x4a4 and +0x4b4 effect handles are finished
 * and cleared. The +0x3c0 transform (44 bytes) is copied into the +0x3b0 node and from there
 * into the +0x3ac item's node. The base tick always runs. */
struct Transform44 { int a[11]; };

struct Ov276Actor {
    char pad000[0x3ac];
    char **ppItem3ac;
    char *pNode3b0;
    char pad3b4[0xc];
    struct Transform44 xform3c0;
};

extern void func_0203c650(int taskList, int handle);
extern void func_ov107_020c7ca4(int actor);

void func_ov276_020d0374(int actor)
{
    struct Ov276Actor *self = (struct Ov276Actor *)actor;

    if ((*(unsigned char *)(actor + 0x1c4) & 0xa) != 0) {
        if (*(signed char *)(actor + 0x1c7) == -1 && *(signed char *)(actor + 0x1c6) == 6) {
            ((signed char *)actor)[0x1c7] = 2;
        }
    }
    if (*(signed char *)(actor + 0x1c6) != 6) {
        if (*(int *)(actor + 0x4a4) != 0) {
            func_0203c650(*(int *)(actor + 0x3c), *(int *)(actor + 0x4a4));
            *(int *)(actor + 0x4a4) = 0;
        }
        if (*(int *)(actor + 0x4b4) != 0) {
            func_0203c650(*(int *)(actor + 0x3c), *(int *)(actor + 0x4b4));
            *(int *)(actor + 0x4b4) = 0;
        }
    }
    *(struct Transform44 *)(self->pNode3b0 + 0x10) = self->xform3c0;
    *(struct Transform44 *)(*self->ppItem3ac + 0x10) = *(struct Transform44 *)(self->pNode3b0 + 0x10);
    func_ov107_020c7ca4(actor);
}
