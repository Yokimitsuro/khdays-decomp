/* Spin physics tick of the ov238 actor: its +0x18 heading turns toward +0x1c at 0.033 per frame and
 * orients the pose about up; the +0xf0 velocity mirrors +0xc, which damps to 0.75. In moves 2-4 the
 * +0x28 timer runs down (to 0). Once the health (+0x21a) is out it is clamped to 0 and, outside move 9,
 * the +0x384 rider is flagged (+0x390) and the next move is 9. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;
struct Mover { char pad[0xf0]; Vec3 vel; };
struct Health { char pad[0x21a]; short hp; };
struct Ov238Node { int actor; char pad[8]; Vec3 vel; };

extern int func_0203d040(int a, int b, int c, int d);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_0203c9d0(void *srt, const Quat *rot);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern const Vec3 data_02042264;

void func_ov238_020d0e08(int *node)
{
    int *state = (int *)node[1];
    Quat q;

    state[6] = func_0203d040(state[6], state[7], 0x88, 0);
    func_0202f188(&q, &data_02042264, state[6]);
    func_0203c9d0((void *)(*state + 0xa0), &q);
    ((struct Mover *)*state)->vel = ((struct Ov238Node *)state)->vel;
    func_01ffa724(0xc00, (Vec3 *)(state + 3), (Vec3 *)(state + 3));
    if (!(*(signed char *)(*state + 0x1c6) != 2 && *(signed char *)(*state + 0x1c6) != 3 &&
          *(signed char *)(*state + 0x1c6) != 4)) {
        state[0xa] -= *(int *)(node[0] + 0x2c);
        if (state[0xa] <= 0) {
            state[0xa] = 0;
        }
    }
    if (((struct Health *)*state)->hp > 0) {
        return;
    }
    ((struct Health *)*state)->hp = 0;
    if (*(signed char *)(*state + 0x1c6) == 9) {
        return;
    }
    *(int *)(*(int *)(*state + 0x384) + 0x390) = 1;
    *(unsigned char *)(*state + 0x1c7) = 9;
}
