/* Drift tick of an ov255 spawned object: the +8 step is the forward axis turned by the +0x20
 * orientation and scaled by the +0x18 speed; the +0x1c timer accumulates the frame rate and past
 * 0.25 the owner's sub-state 0 is requested. */
typedef struct { int x, y, z; } Vec3;

extern void func_0202f384(Vec3 *out, void *q, const Vec3 *in);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042258;

void func_ov255_020d24bc(int *node)
{
    int *obj = (int *)node[1];
    Vec3 fwd;

    func_0202f384(&fwd, (void *)obj[8], &data_02042258);
    func_01ffa724(obj[6], &fwd, (Vec3 *)(obj + 2));
    obj[7] += *(int *)(node[0] + 0x2c);
    if (obj[7] <= 0x400) {
        return;
    }
    *(unsigned char *)(obj[0] + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
