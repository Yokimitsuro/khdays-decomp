typedef unsigned char u8;
struct Actor;
typedef void (*ActorCallback)(u8 val, struct Actor *self);

struct Actor {
    u8 pad000[0x3a4];
    ActorCallback cb;     /* 0x3a4 */
    u8 pad3a8[4];
    u8 *target;           /* 0x3ac */
};

struct Task {
    struct Actor *actor;  /* 0x00 */
    int field_04;
    int field_08;
    int field_0c;
};

extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(int *a, int i, int v);

void func_ov291_020cd524(int *node)
{
    struct Task *state = (struct Task *)node[1];
    struct Actor *actor;
    ActorCallback cb;

    func_ov107_020c5af8((int)state->actor, 0x16f, 6, state->field_0c);
    actor = state->actor;
    cb = actor->cb;
    if (cb != 0) {
        cb(actor->target[0x1b4], actor);
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
