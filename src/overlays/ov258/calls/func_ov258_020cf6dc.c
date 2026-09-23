/* Swing hit test of the ov258 actor: after re-acquiring the target (020cd028) a 96.0-long capsule of
 * radius 12.6 stands upright at the +0x1c point (0.25 high); it hits with a random flat push of up
 * to 1.0 each way (kind 4, effect 1) through 020cd104. */
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; Vec3 axis; int length; int radius; } Capsule;

extern int func_ov258_020cd028(int *node, int face);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_02023eb4(int bound);
extern int func_ov258_020cd104(int *node, void *sphere, void *box, void *capsule, void *segment, Vec3 *push, int once, int effect, int kind);
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042264;

void func_ov258_020cf6dc(int *node)
{
    int *state = (int *)node[1];
    Capsule cap;
    Vec3 push;

    func_ov258_020cd028(node, 0);
    cap.pos = *(Vec3 *)(state + 7);
    cap.pos.y = 0x400;
    cap.axis = data_02042264;
    cap.length = 0x60000;
    cap.radius = 0xc900;
    VEC_Subtract((Vec3 *)(*(int *)(*state + 0x454) + 0x190), (Vec3 *)(state + 7), &push);
    func_01ff8d18(&push, &push);
    push = data_02041dc8;
    push.x = func_02023eb4(0x2001) - 0x1000;
    push.z = func_02023eb4(0x2001) - 0x1000;
    func_ov258_020cd104(node, 0, 0, &cap, 0, &push, 0, 1, 4);
}
