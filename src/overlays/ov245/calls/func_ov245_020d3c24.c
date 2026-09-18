/* func_ov245_020d3c24 -- teardown of the mounted pose chain: copies the +0x3b0 source's +4
 * transform into the +0x398 item's +0x10 and that into the +0x388 target's +0x10; for each of
 * the three +0x38c parts stores its +0x3a4 anchor's +0x14 position at +0x58, normalises the
 * offset from there to the next anchor's +0x14 into +0x64 and keeps the length at +0x70;
 * then the base teardown (020c7ca4). */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[11]; } Pose44;
struct Ov245Item { char pad[0x10]; Pose44 pose; };
struct Ov245Src { char pad[4]; Pose44 pose; };
struct Ov245Chain {
    char pad[0x38c];
    int parts[3];      /* +0x38c */
    int items[3];      /* +0x398 */
    int anchors[4];    /* +0x3a4: each part spans anchors[i]..anchors[i + 1] */
};

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_ov107_020c7ca4(int self);

void func_ov245_020d3c24(int self) {
    Vec3 d;
    int i;

    ((struct Ov245Item *)*(int *)(self + 0x398))->pose = ((struct Ov245Src *)*(int *)(self + 0x3b0))->pose;
    ((struct Ov245Item *)**(int **)(self + 0x388))->pose = ((struct Ov245Item *)*(int *)(self + 0x398))->pose;
    for (i = 0; i < 3; i++) {
        int part = ((struct Ov245Chain *)self)->parts[i];
        *(Vec3 *)(part + 0x58) = *(Vec3 *)(((struct Ov245Chain *)self)->anchors[i] + 0x14);
        VEC_Subtract((Vec3 *)(((struct Ov245Chain *)self)->anchors[i + 1] + 0x14), (Vec3 *)(part + 0x58), &d);
        *(int *)(part + 0x70) = func_01ff8d18(&d, (Vec3 *)(part + 0x64));
    }
    func_ov107_020c7ca4(self);
}
