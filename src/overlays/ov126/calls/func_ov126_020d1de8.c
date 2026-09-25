/* Twin-shot tick of the ov126 enemy (byte-identical twin of ov125 020ce1a8): the +0x3c speed is
 * fifteen times the frame rate and the +0x2c clock runs up at it; past 0x300 the owner's +0x24 hook
 * hears message pair 3 of data_ov126_020d400c, and the first two idle +0x3a0 shots are launched
 * (020d3430) from the +0x394 / +0x398 hand points along the +0x58 facing. Each round counts the
 * +0x50 volleys down: while some remain the clock is re-armed to 0x100..0x300 and 020d1cb8 runs
 * again, otherwise +0x54 is re-rolled within the owner's +0x224..+0x228 range and sub-state 2
 * follows. */
typedef struct { int x, y, z; } Vec3;
struct hw60 { unsigned short lo : 8, hi : 8; };
struct Owner { char pad[0x3a0]; int kids[2]; };

extern void func_0202f384(Vec3 *out, const void *m, const Vec3 *in);
extern void func_ov126_020d3430(int child, void *from, Vec3 *dir);
extern int func_02023eb4(int n);
extern void func_0203c634(int *node, int slot, void *cb);
/* data_ov126_020d400c: the enemy's four owner-message pairs. This tick copies pair 3 as a typed
 * struct member; read as two u16 elements the copy is scheduled differently. */
typedef struct { unsigned short a, b; } MsgPair;
typedef struct { MsgPair pairs[4]; } Ov126MsgPairs;
extern Ov126MsgPairs data_ov126_020d400c;
extern const Vec3 data_02042258;
extern void func_ov126_020d1cb8(int *node);

static inline int RandRange(int low, int high)
{
    int span = high - low;
    if (span < 0) span = -span;
    return low + func_02023eb4(span + 1);
}

void func_ov126_020d1de8(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    void *from[2];
    unsigned short pair[2];
    unsigned short *pp;
    void (*cb)();
    int launched;
    int i;

    state[0xf] = *(int *)(*node + 0x2c) * 30 / 2;
    state[0xb] += *(int *)(*node + 0x2c);
    if (state[0xb] <= 0x300) {
        return;
    }
    from[0] = (void *)(*(int *)(*state + 0x394) + 0x14);
    from[1] = (void *)(*(int *)(*state + 0x398) + 0x14);
    launched = 0;
    pp = pair;
    *(MsgPair *)pp = data_ov126_020d400c.pairs[3];
    cb = *(void (**)())(*state + 0x24);
    if (cb != 0) cb(*state, pp, 4);
    for (i = 0; i < 2; i++) {
        if ((((struct hw60 *)(((struct Owner *)*state)->kids[i] + 0x60))->lo & 1) == 0) {
            func_0202f384(&dir, state + 0x16, &data_02042258);
            func_ov126_020d3430(((struct Owner *)*state)->kids[i], from[launched++], &dir);
            if (launched == 2) {
                break;
            }
        }
    }
    if (--state[0x14] == 0) {
        state[0x15] = RandRange(*(int *)(*state + 0x224), *(int *)(*state + 0x228));
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[0xb] = RandRange(0x100, 0x300);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov126_020d1cb8);
}
