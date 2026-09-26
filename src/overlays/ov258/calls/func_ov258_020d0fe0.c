/* Update of the ov258 beam: its rig clears flag 1 and the +0x28 / +0x2c clocks run up at the frame
 * rate. On the first frame (+0x48) the beam aims from the owner's +0x44c hand at the target 13.6 high:
 * the look rotation is kept in +0x38, its length (less the owner radius and 1.0) in +0x30, and the
 * sweep starts a quarter turn to the +0x4a side. Later frames sweep that quarter turn back across
 * (1.57 - 6.28 x 1/+0x2c, mirrored by +0x4a) and cut the length at the first wall hit within 48.0.
 * Each frame the beam direction is stored in the owner's +0x3f8 slot, the beam rig sits on the
 * +0x44c / +0x450 hand (by +0x49) stretched to 1/3 + 1/7 of the length, the glow rig at the tip
 * (3.0), and the rotation is copied to the owner's +0x410. After 0x500 once the rig is idle, the
 * beam releases its owner effect slots (+0x49 and 0x26 / 0x27), hides the glow and ends. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;
typedef struct { int m[9]; } Mtx33;
struct EffectPair { int res; int handle; };
struct Ov258Effects { char pad[0x464]; struct EffectPair pair[0x30]; };
struct Joint { char pad[0x14]; Vec3 pos; };
struct Ov258Beams { char pad[0x3f8]; Vec3 dirs[2]; };

extern void func_0203cd7c(Mtx33 *out, const Vec3 *target, const Vec3 *from, const Vec3 *up);
extern void func_0202ea48(Quat *out, const Mtx33 *m);
extern void func_0202f384(Vec3 *out, const Quat *q, const Vec3 *in);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern void func_0202f4a4(Quat *out, Quat *in);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_0202ef54(Quat *out, const Quat *a, const Quat *b);
extern void func_0203ca30(void *transform, const Vec3 *translation);
extern void func_0203c9d0(void *srt, const Quat *rot);
extern void func_0203ca50(void *transform, int x, int y, int z);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int FX_Inv(int value, int denom);
extern int func_01fff920(int collision, Vec3 *start, Vec3 *ray);
extern void func_01ffd144(int scale, Vec3 *in, Vec3 *out);
extern void func_0203c640(int *node);
extern const Vec3 data_02042258;
extern const Vec3 data_02042264;

static inline int FX_MUL(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}
/* position of the hand the beam leaves from: +0x44c when +0x49 is 0x19, else +0x450. The ternary picks
 * the position itself (picking the joint and taking ->pos after it colours the select differently). */
#define HAND_POS(st) (*((signed char *)(st) + 0x49) == 0x19 ? &(*(struct Joint **)((st)[2] + 0x44c))->pos \
                                                     : &(*(struct Joint **)((st)[2] + 0x450))->pos)

void func_ov258_020d0fe0(int *node)
{
    int *state = (int *)node[1];
    Mtx33 look;
    Vec3 d;
    Vec3 fwd;
    Vec3 target;
    Quat q;
    Vec3 unit;
    Vec3 tip;
    Vec3 dir;
    Quat rot;
    Vec3 ray;
    Vec3 start;
    Vec3 end;

    *(int *)(state[0] + 0x5c) &= ~2;
    state[0xa] += *(int *)(node[0] + 0x2c);
    state[0xb] += *(int *)(node[0] + 0x2c);
    if (*((u8 *)state + 0x48) == 0) {
        (*((u8 *)state + 0x48))++;
        target = *(Vec3 *)(state[3] + 0x190);
        target.y = 0xda00;
        func_0203cd7c(&look, &target, (Vec3 *)(*(int *)(state[2] + 0x44c) + 0x14), &data_02042264);
        func_0202ea48(&q, &look);
        func_0202f384(&fwd, &q, &data_02042258);
        VEC_Subtract(&target, (Vec3 *)(*(int *)(state[2] + 0x44c) + 0x14), &d);
        unit = d;
        state[0xc] = func_01ff8d18(&unit, &unit);
        state[0xc] -= *(int *)(state[2] + 0x80) + 0x1000;
        d.y = 0;
        func_01ff8d18(&d, &d);
        VEC_DotProduct(&fwd, &d);
        func_0202f4a4(&q, &q);
        *(Quat *)(state + 0xe) = q;
        func_0202f188(&q, &data_02042264, *((signed char *)state + 0x4a) == 0 ? 0x1922 : -0x1922);
        func_0202ef54(&q, &q, (Quat *)(state + 0xe));
        func_0202f384(&fwd, &q, &data_02042258);
        ((struct Ov258Beams *)state[2])->dirs[*((signed char *)state + 0x4a)] = fwd;
        func_0203ca30((void *)(state[0] + 4), HAND_POS(state));
        func_0203c9d0((void *)(state[0] + 4), &q);
        func_0203ca50((void *)(state[0] + 4), 0x1000, 0x1000, state[0xc] / 3 + state[0xc] / 7);
        func_01ffa724(state[0xc], &((Vec3 *)(state[2] + 0x3f8))[*((signed char *)state + 0x4a)], &tip);
        VEC_Add(&tip, HAND_POS(state), &tip);
        func_0203ca30((void *)(state[1] + 4), &tip);
        func_0203ca50((void *)(state[1] + 4), 0x3000, 0x3000, 0x3000);
        *(Quat *)(state[2] + 0x410) = q;
    } else {
        int t = FX_Inv(state[0xb], 0x1000);
        int world;
        int hit;

        func_0202f188(&rot, &data_02042264,
                      (*((signed char *)state + 0x4a) == 0 ? 0x1922 : -0x1922) +
                          FX_MUL(*((signed char *)state + 0x4a) == 0 ? -0x6488 : 0x6488, t));
        func_0202ef54(&rot, &rot, (Quat *)(state + 0xe));
        func_0202f384(&dir, &rot, &data_02042258);
        ((struct Ov258Beams *)state[2])->dirs[*((signed char *)state + 0x4a)] = dir;
        start = *(Vec3 *)(*(int *)(state[2] + 0x44c) + 0x14);
        world = *(int *)(state[2] + 4);
        func_01ffa724(0x30000, &dir, &ray);
        hit = func_01fff920(*(int *)(world + 0x7c), &start, &ray);
        if (hit != 0) {
            func_01ffd144(*(int *)(hit + 0xc), &ray, &dir);
            state[0xc] = func_01ff8d18(&dir, &dir);
        }
        func_0203ca30((void *)(state[0] + 4), HAND_POS(state));
        func_0203c9d0((void *)(state[0] + 4), &rot);
        func_0203ca50((void *)(state[0] + 4), 0x1000, 0x1000, state[0xc] / 3 + state[0xc] / 7);
        func_01ffa724(state[0xc], &((Vec3 *)(state[2] + 0x3f8))[*((signed char *)state + 0x4a)], &end);
        VEC_Add(&end, HAND_POS(state), &end);
        func_0203ca30((void *)(state[1] + 4), &end);
        func_0203ca50((void *)(state[1] + 4), 0x3000, 0x3000, 0x3000);
        *(Quat *)(state[2] + 0x410) = rot;
    }
    if (state[0xa] < 0x500 && *(u8 *)(state[0] + 0xad) != 0) {
        return;
    }
    ((struct Ov258Effects *)state[2])->pair[*((signed char *)state + 0x49)].handle = 0;
    *(int *)(state[1] + 0x5c) |= 2;
    ((struct Ov258Effects *)state[2])->pair[*((signed char *)state + 0x49) == 0x19 ? 0x26 : 0x27].handle = 0;
    func_0203c640(node);
}
