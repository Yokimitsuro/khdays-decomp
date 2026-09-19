/* func_ov253_020d23d8 -- place the mounted actor: its +0xa0 placement takes the +0x388 item's
 * +0x394 joint anchor, the +0x44c rotation about data_02042264 and the +0x38c offset scaled by
 * +0x398; the +0x3a0 item's animation advances (0202a818) and the actor updates (020c6980),
 * then the placement is copied into the +0x3d4 item's +0x10. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[11]; } Pose44;
struct Ov253Placed { char pad[0x10]; Pose44 pose; };
struct Ov253Self { char pad[0xa0]; Pose44 pose; };

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0203ca30(void *srt, const Vec3 *translation);
extern void func_0203c9b4(void *srt, const Vec3 *axis, int angle);
extern void func_0203ca74(void *srt, const Vec3 *offset);
extern int func_0202a818(void *animation, int delta);
extern void func_ov107_020c6980(int self, int delta);
extern const Vec3 data_02042264;

void func_ov253_020d23d8(int self, int delta) {
    int item = *(int *)(self + 0x388);
    Vec3 offset;

    func_01ffa724(*(int *)(self + 0x398), (Vec3 *)(self + 0x38c), &offset);
    func_0203ca30((void *)(self + 0xa0), (Vec3 *)(*(int *)(item + 0x394) + 0x14));
    func_0203c9b4((void *)(self + 0xa0), &data_02042264, *(int *)(item + 0x44c));
    func_0203ca74((void *)(self + 0xa0), &offset);
    func_0202a818(*(void **)(*(int *)(self + 0x3a0) + 0x88), delta);
    func_ov107_020c6980(self, delta);
    ((struct Ov253Placed *)*(int *)(self + 0x3d4))->pose = ((struct Ov253Self *)self)->pose;
}
