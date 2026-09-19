/* Sweep strike tick of the ov137 enemy (the Ov143_StepSlamStrike shape). The +0x14 direction
 * scaled by the +0x20 length becomes the +8 vector, and the query is the segment from the +4
 * point along that direction (radius 0x800). Mode 0 (+0x24) sweeps the actor list of the +0x38c
 * item and asks the shared checker whether each candidate is hit along the +8 vector; the first
 * acceptance ends the action. Mode 1 instead locks on, fills a request with the item's id, the
 * object's kind and the lock handle (flags 0x2024) and, if the handle's +8 bit 0 is set and the
 * lock is taken, ends the action. Either ending sends the position message, fires reaction 0x11d
 * mode 7 (0 / 0x53 for the lock) at the +4 point and clears the sub-state. Otherwise the +0x28
 * distance advances by the length and the action ends once the object reports contact or the
 * distance passes 30.0. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Vec3 { int x, y, z; };
struct Segment { struct Vec3 origin; struct Vec3 dir; int nLength; int nRadius; };
struct HitWord { u32 lo : 16, hi : 16; };

struct HitCommand {
    struct HitWord flags00;
    struct Vec3 vector04;
    u32 field10;
    u32 field14;
    void *hit18;
    int pad1c[4];
};

struct Ov137Contact { u8 bGrounded : 1, bBlocked : 1; };
struct Ov137Byte8 { u32 lo : 8, rest : 24; };

extern void func_01ffa724(int scale, const struct Vec3 *src, struct Vec3 *dst);
extern int func_ov107_020c8f44(int item, struct Segment *query, int *results);
extern int func_ov107_020ca918(int ent, int actor, int item, int mode, void *dir, int flag);
extern void func_ov138_020d2e94(int *state);
extern void func_ov107_020c5af8(int item, int id, int a, void *at);
extern void func_0203c634(int *node, int slot, void *value);
extern int func_ov107_020c9184(int actor, struct Segment *query, void **out);
extern int func_ov107_020c5cfc(int lock, int param, struct HitCommand *req);
extern struct Vec3 data_02041dc8;

void func_ov138_020d2ba8(int *node)
{
    int *state = (int *)node[1];
    struct Segment query;
    int results[4];
    void *handle;
    int lock;
    int i;
    int n;

    func_01ffa724(state[8], (struct Vec3 *)(state + 5), (struct Vec3 *)(state + 2));
    query.origin = *(struct Vec3 *)state[1];
    query.dir = *(struct Vec3 *)(state + 5);
    query.nLength = state[8];
    query.nRadius = 0x800;

    if (state[9] == 0) {
        n = func_ov107_020c8f44(*(int *)(*state + 0x38c), &query, results);
        i = 0;
        if (n > 0) {
            do {
                if (func_ov107_020ca918(results[i], *state, *(int *)(*state + 0x38c), 1, state + 2, 0) != 0) {
                    func_ov138_020d2e94(state);
                    func_ov107_020c5af8(*(int *)(*state + 0x38c), 0x11d, 7, (void *)state[1]);
                    *(u8 *)(*state + 0x1c7) = 0;
                    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
                    return;
                }
            } while (++i < n);
        }
    } else {
        struct HitCommand spare = { 0 };

        if ((lock = func_ov107_020c9184(*state, &query, &handle)) != 0
            && (*(u16 *)(lock + 0x100 + 0xac) & 4) == 0) {
            struct HitCommand req = { 0 };

            req.flags00.lo = 0x2024;
            req.vector04 = data_02041dc8;
            req.flags00.hi = 0;
            req.field10 = (req.field10 & 0xffff0000) | *(u16 *)(*(int *)(*state + 0x38c) + 0x200 + 0x96);
            req.field14 = (req.field14 & 0xffff0000) | (u16)*(int *)(*state + 0x258);
            req.hit18 = handle;
            if ((((struct Ov137Byte8 *)((char *)handle + 8))->lo & 1) != 0
                && func_ov107_020c5cfc(lock, *(int *)(*state + 0x25c), &req) != 0) {
                func_ov138_020d2e94(state);
                func_ov107_020c5af8(*(int *)(*state + 0x38c), 0, 0x53, (void *)state[1]);
                *(u8 *)(*state + 0x1c7) = 0;
                func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
                return;
            }
        }
    }

    state[0xa] += state[8];
    if (((struct Ov137Contact *)(*state + 0x17a))->bGrounded == 0
        && ((struct Ov137Contact *)(*state + 0x17a))->bBlocked == 0
        && state[0xa] <= 0x1e000) {
        return;
    }
    func_ov138_020d2e94(state);
    func_ov107_020c5af8(*(int *)(*state + 0x38c), 0x11d, 7, (void *)state[1]);
    *(u8 *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
