/* Steering helper of the ov235 states: returns the gap from the owner to the target (the distance
 * between their +0x74 centres less both +0x80 radii; 0 without a target) and turns the +0x2c
 * orientation towards it. For the owner kinds 4, 6 and 7 (+0x1c6) the heading blends the tangent
 * of the circle about the origin (flipped to the target's side) with the direct direction, by how
 * well the target and the owner line up from the origin; otherwise it faces the target about
 * data_02042264. The +0x3a8 part's motion step (020c9f48) is then turned by the +0x1c
 * orientation and stored in *dir, its speed in *speed (either may be null). */
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;

extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0202ed60(Quat *out, const Vec3 *a, const Vec3 *b);
extern int func_020050b4(int y, int x);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern int func_ov107_020c9f48(int part, Vec3 *out);
extern void func_0202f384(Vec3 *out, void *q, const Vec3 *in);
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042264;
extern const Vec3 data_02042258;

static inline void VEC_Set(Vec3 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

int func_ov235_020cccc0(int *state, int target, Vec3 *dir, int *speed)
{
    Vec3 step;
    Vec3 d;
    Vec3 other;
    Vec3 self;
    Vec3 flat;
    Vec3 side;
    int owner;
    int gap;
    int kind;
    int s;

    if (target != 0) {
    owner = *state;
    VEC_Subtract((void *)(target + 0x74), (void *)(owner + 0x74), &d);
    gap = func_01ff8d18(&d, &d) - *(int *)(owner + 0x80) - *(int *)(target + 0x80);
    kind = *(signed char *)(*state + 0x1c6);
    if (!(kind != 4 && kind != 6 && kind != 7)) {
        Vec3 blend = {0, 0, 0};
        int dot;

        VEC_Subtract(&data_02041dc8, (void *)(target + 0x74), &other);
        other.y = 0;
        func_01ff8d18(&other, &other);
        VEC_Subtract(&data_02041dc8, (void *)(owner + 0x74), &self);
        self.y = 0;
        func_01ff8d18(&self, &self);
        flat = d;
        flat.y = 0;
        func_01ff8d18(&flat, &flat);
        VEC_CrossProduct(&data_02042264, &self, &side);
        dot = VEC_DotProduct(&other, &self);
        if (dot < 0) {
            dot = 0;
        }
        if ((long long)self.x * other.z - (long long)self.z * other.x < 0) {
            func_01ffa724(-0x1000, &side, &side);
        }
        blend.x = (int)(((long long)flat.x * dot + (long long)side.x * (0x1000 - dot) + 0x800) >> 12);
        blend.z = (int)(((long long)flat.z * dot + (long long)side.z * (0x1000 - dot) + 0x800) >> 12);
        func_0202ed60((Quat *)(state + 0xb), &data_02042258, &blend);
    } else {
        func_0202f188((Quat *)(state + 0xb), &data_02042264, func_020050b4(d.x, d.z));
    }
    s = func_ov107_020c9f48(*(int *)(*state + 0x3a8), &step);
    func_0202f384(&step, state + 7, &step);
    if (dir != 0) {
        *dir = step;
    }
    if (speed != 0) {
        *speed = s;
    }
    return gap;
    }
    return 0;
}
