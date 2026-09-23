/* Update of the ov238 actor: in phase 1 without a target, while its +0x398 partner carries a rider
 * (+0x3f0), it rides along: placed at the rider's +0x14 point (020c5c54) and oriented by the rider's
 * +4 rotation after the up-to-normal tilt. The base update runs, the +0xa0 pose is copied to the
 * +0x38c model and mirrored onto the +0x388 set's first model. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;
typedef struct { int w[11]; } SrtTransform;
struct Posed { char pad[0x10]; SrtTransform srt; };
struct Ov238Actor { char pad[0xa0]; SrtTransform pose; };

extern void func_ov107_020c5c54(char *self, void *at);
extern void func_0202ed60(Quat *out, const Vec3 *from, const Vec3 *to);
extern void func_0202ef54(Quat *out, const Quat *a, const Quat *b);
extern void func_0203c9d0(void *srt, const Quat *rot);
extern void func_ov107_020c6980(void *obj, int arg2);
extern const Vec3 data_02042264;

void func_ov238_020d2834(char *self, int arg)
{
    Vec3 normal;
    Quat q;
    int ride = 0;

    if (*(int *)(self + 0x50) == 1) {
        if (*(int *)(self + 0x390) == 0) {
            ride = *(int *)(*(int *)(self + 0x398) + 0x3f0);
        }
        if (ride != 0) {
            func_ov107_020c5c54(self, (void *)(ride + 0x14));
            func_0202ed60(&q, &data_02042264, &normal);
            func_0202ef54(&q, (Quat *)(ride + 4), &q);
            func_0203c9d0(self + 0xa0, &q);
        }
    }
    func_ov107_020c6980(self, arg);
    (*(struct Posed **)(self + 0x38c))->srt = ((struct Ov238Actor *)self)->pose;
    (**(struct Posed ***)(self + 0x388))->srt = (*(struct Posed **)(self + 0x38c))->srt;
}
