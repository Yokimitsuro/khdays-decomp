/* Ring slot writer of the ov223 enemy: fills the next 0x38-byte entry of the owner's +0x90
 * ring (index +4) with scale 1.0, radius 0.5, the given point at +0x2c and a pose at +8 made
 * of a -0x1922 turn about data_02042270 combined with the given pose (ef54); the index then
 * advances modulo the owner's +0x8c count. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int q[4]; } Quat;

struct Ov223RingEntry {
    int nScale;
    int nRadius;
    Quat pose;
    char pad18[0x14];
    Vec3 vPoint;
};

extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_0202ef54(Quat *out, const Quat *a, const Quat *b);
extern const Vec3 data_02042270;

void func_ov223_020d4e70(int *state, const Vec3 *pPoint, const Quat *pPose)
{
    struct Ov223RingEntry *entry = &((struct Ov223RingEntry *)*(int *)(*state + 0x90))[state[1]];

    entry->nScale = 0x1000;
    entry->nRadius = 0x800;
    entry->vPoint = *pPoint;
    func_0202f188(&entry->pose, &data_02042270, -0x1922);
    func_0202ef54(&entry->pose, &entry->pose, pPose);
    state[1] = (state[1] + 1) % *(int *)(*state + 0x8c);
}
