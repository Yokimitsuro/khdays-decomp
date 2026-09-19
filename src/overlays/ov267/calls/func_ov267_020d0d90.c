/* Pre-update of the ov266 enemy: outside mode 9 the +0x620 task is dropped, outside mode 0xc
 * the +0x658 one; the +0x514 offset is reset to (0, 0x1c00, 0), turned by the actor's +0xa0
 * basis and added to the +0xb0 position, then the ov107 actor base finishes the frame. */
typedef struct { int x, y, z; } Vec3;

extern void func_0203c650(int taskList, int task);
extern void func_0202f384(Vec3 *out, void *pose, Vec3 *in);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov107_020c7ca4(int self);

void func_ov267_020d0d90(int self)
{
    if (*(signed char *)(self + 0x1c6) != 9 && *(int *)(self + 0x620) != 0) {
        func_0203c650(*(int *)(self + 0x3c), *(int *)(self + 0x620));
        *(int *)(self + 0x620) = 0;
    }
    if (*(signed char *)(self + 0x1c6) != 0xc && *(int *)(self + 0x658) != 0) {
        func_0203c650(*(int *)(self + 0x3c), *(int *)(self + 0x658));
        *(int *)(self + 0x658) = 0;
    }
    *(int *)(self + 0x514) = 0;
    *(int *)(self + 0x518) = 0x1c00;
    *(int *)(self + 0x51c) = 0;
    func_0202f384((Vec3 *)(self + 0x114 + 0x400), (void *)(self + 0xa0), (Vec3 *)(self + 0x114 + 0x400));
    VEC_Add((Vec3 *)(self + 0x114 + 0x400), (Vec3 *)(self + 0xb0), (Vec3 *)(self + 0x114 + 0x400));
    func_ov107_020c7ca4(self);
}
