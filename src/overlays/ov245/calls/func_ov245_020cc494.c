/* func_ov245_020cc494 -- pose sync of the carried actor: runs the +0x4c8 and +0x4cc items'
 * motions (020c9ec8), the base sync (020c6980), copies the +0xa0 placement into the +0x3b8
 * item's +0x10 and that into the +0x3b4 target's +0x10, lifts both +0x24 heights by 19.0 and
 * keeps the +0x3b8 item's +0x20 position at +0x3bc. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[11]; } Pose44;
struct Ov245Item { char pad[0x10]; Pose44 pose; };

extern void func_ov107_020c9ec8(int item, int a);
extern void func_ov107_020c6980(int self, int a);

void func_ov245_020cc494(int self, int a) {
    func_ov107_020c9ec8(*(int *)(self + 0x4c8), a);
    func_ov107_020c9ec8(*(int *)(self + 0x4cc), a);
    func_ov107_020c6980(self, a);
    ((struct Ov245Item *)*(int *)(self + 0x3b8))->pose = *(Pose44 *)(self + 0xa0);
    ((struct Ov245Item *)**(int **)(self + 0x3b4))->pose = ((struct Ov245Item *)*(int *)(self + 0x3b8))->pose;
    *(int *)(**(int **)(self + 0x3b4) + 0x24) += 0x4c00;
    *(int *)(*(int *)(self + 0x3b8) + 0x24) += 0x4c00;
    *(Vec3 *)(self + 0x3bc) = *(Vec3 *)(*(int *)(self + 0x3b8) + 0x20);
}
