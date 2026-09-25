/* Launch tick of the ov125 enemy (x2 with ov126). The +0x3c rate is the owner's frame rate x 15;
 * once the +0x2c timer (fed by the owner's rate) passes 0x300 message pair 3 of
 * data_ov125_020d03cc goes to the owner's +0x24 hook, and each of the two children listed at the owner's
 * +0x3a0 whose +0x60 low byte has bit 0 clear is launched (020cf7f0) from the next of the
 * +0x394/+0x398 parts' +0x14 points along the +0x58 facing's forward axis. When the +0x50 volley
 * count runs out, the +0x54 cooldown is re-rolled in [+0x224, +0x228], sub-state 2 is requested
 * and the tick ends; otherwise the timer restarts at a random 0x100..0x300 and the tick hands
 * over to func_ov125_020ce078. */
typedef struct { int x, y, z; } Vec3;
struct hw60 { unsigned short lo : 8, hi : 8; };
struct Owner { char pad[0x3a0]; int kids[2]; };

extern void func_0202f384(Vec3 *out, const void *m, const Vec3 *in);
extern void func_ov125_020cf7f0(int child, void *from, Vec3 *dir);
extern int func_02023eb4(int n);
extern void func_0203c634(int *node, int slot, void *cb);
/* data_ov125_020d03cc: the enemy's four owner-message pairs. This tick copies pair 3 as a typed
 * struct member; read as two u16 elements the copy is scheduled differently. */
typedef struct { unsigned short a, b; } MsgPair;
typedef struct { MsgPair pairs[4]; } Ov125MsgPairs;
extern Ov125MsgPairs data_ov125_020d03cc;
extern const Vec3 data_02042258;
extern void func_ov125_020ce078(int *node);

static inline int RandRange(int low, int high)
{
    int span = high - low;
    if (span < 0) span = -span;
    return low + func_02023eb4(span + 1);
}

void func_ov125_020ce1a8(int *node)
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
    *(MsgPair *)pp = data_ov125_020d03cc.pairs[3];
    cb = *(void (**)())(*state + 0x24);
    if (cb != 0) cb(*state, pp, 4);
    for (i = 0; i < 2; i++) {
        if ((((struct hw60 *)(((struct Owner *)*state)->kids[i] + 0x60))->lo & 1) == 0) {
            func_0202f384(&dir, state + 0x16, &data_02042258);
            func_ov125_020cf7f0(((struct Owner *)*state)->kids[i], from[launched++], &dir);
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
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov125_020ce078);
}
