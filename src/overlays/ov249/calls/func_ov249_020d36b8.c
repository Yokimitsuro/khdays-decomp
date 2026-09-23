/* Swell tick of the ov249 actor: while the +0x4c clock is short of 0.4 it runs up at the frame rate
 * (capped there) and a kind-2 contact sphere at the +0x34 point grows with it (radius 0 to 4.0 over the
 * first 0.27). Once the +4 rig is idle the next move is 2 and the brain slot +0x20 clears. */
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int radius; } Sphere;
typedef struct { Vec3 pos; Vec3 axis[3]; int radius; int flag; } Cylinder;

extern void func_ov249_020d0c28(int *state, int kind, Sphere *sphere, void *box);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov249_020d36b8(int *node)
{
    int *state = (int *)node[1];
    Cylinder shape;
    Sphere sphere;
    int t;

    if (state[0x13] < 0x660) {
        state[0x13] += *(int *)(node[0] + 0x2c);
        state[0x13] = state[0x13] > 0x660 ? 0x660 : state[0x13];
        shape.pos = *(Vec3 *)(state + 0xd);
        t = state[0x13];
        if (t > 0x440) {
            t = 0x440;
        } else if (t < 0) {
            t = 0;
        }
        shape.radius = t * 0x4000 / 0x440;
        sphere.pos = shape.pos;
        sphere.radius = shape.radius;
        func_ov249_020d0c28(state, 2, &sphere, 0);
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    *(signed char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
