/* Charge-hit tick of the ov237 actor: while fewer than three charge steps remain (+0x34) the +0x3c
 * push turns flat toward the +0x3dc target at 0.1875; a 3.0 sphere 2.0 above the +0x38 point hits
 * with push data_ov237_020d1b64 (effect 1, kind 4) and counts hits in +0x55. When the +4 rig
 * finishes: out of steps, blocked (+0x17a bit 1), after five hits or with a +0x4b4 hold the charge
 * ends (pose 0x14, effect 0x11 unless held, then 020cfe70); otherwise a step is spent and pose 0x13
 * replays (effect 0x10 unless held). */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int radius; } Sphere;
typedef struct { u8 b0 : 1; u8 b1 : 1; } Bits;

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov237_020cdbe4(int *node, void *sphere, void *box, void *segment, Vec3 *push, int once, unsigned short effect, int kind);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov237_020cfe70(void);
extern const Vec3 data_ov237_020d1b64;

void func_ov237_020cfc88(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    Sphere sphere;
    Vec3 push;

    push = data_ov237_020d1b64;
    if (state[0xd] < 3) {
        VEC_Subtract((Vec3 *)(*(int *)(*state + 0x3dc) + 0x190), (Vec3 *)(*state + 0xb0), &dir);
        dir.y = 0;
        func_01ff8d18(&dir, &dir);
        func_01ffa724(0x300, &dir, &dir);
        *(Vec3 *)(state + 0xf) = dir;
    }
    sphere.pos = *(Vec3 *)state[0xe];
    sphere.pos.y += 0x2000;
    sphere.radius = 0x3000;
    if (func_ov237_020cdbe4(node, &sphere, 0, 0, &push, 0, 1, 4) != 0) {
        (*((u8 *)state + 0x55))++;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0xd] == 0 || ((Bits *)(*state + 0x17a))->b1 || *((u8 *)state + 0x55) >= 5 ||
        *(int *)(*state + 0x4b4) != 0) {
        func_ov107_020c9264(*state, 0x14, 0);
        if (*(int *)(*state + 0x4b4) == 0) {
            func_ov107_020c0b90(*state, 0x11, *(Vec3 *)state[0xe], 0);
        }
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov237_020cfe70);
        return;
    }
    state[0xd]--;
    func_ov107_020c9264(*state, 0x13, 0);
    if (*(int *)(*state + 0x4b4) != 0) {
        return;
    }
    func_ov107_020c0b90(*state, 0x10, *(Vec3 *)state[0xe], 0);
}
