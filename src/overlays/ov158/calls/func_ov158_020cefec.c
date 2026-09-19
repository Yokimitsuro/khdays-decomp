/* Sweep strike tick of the ov158 enemy (the Ov143_StepSlamStrike shape). In mode 0 (+0x24) the
 * +0x14 direction first eases (x/z by a tenth, y by a fifth) towards the unit direction from the
 * +4 point to the best-facing entity of the collision owner's +0xa8 list (flag bit 1 of +0x40
 * and bit 0 of +0x60 set, dot product above 0x400) and is re-normalised. The direction scaled
 * by the +0x20 length becomes the +8 vector, and the query is the segment from the +4 point
 * along it (radius 0xe00). Mode 0 sweeps the actor list of the +0x38c item and asks the shared
 * checker whether each candidate is hit along the +8 vector; the first acceptance ends the
 * action with reactions 0x150 mode 8 and 7. Mode 1 instead locks on, fills a request with the
 * item's id, the object's kind and the lock handle (flags 0x2024) and, if the handle's +8 bit 0
 * is set and the lock is taken, ends the action with reaction 0 / 0x53. Either ending sends the
 * position message at the +4 point and clears the sub-state. Otherwise the +0x28 distance
 * advances by the length and the action ends (reaction 0x150 mode 7) once the object reports
 * contact or the distance passes 30.0. */
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

struct Ov158Contact { u8 bGrounded : 1, bBlocked : 1; };
struct Ov158Bits40 { int b0 : 1, b1 : 1; };
struct Ov158HalfByte { u16 lo : 8, hi : 8; };
struct Ov158Byte8 { u32 lo : 8, rest : 24; };

extern char **func_01fffd70(void *list);
extern char **func_01fffd8c(void *list);
extern void VEC_Subtract(const struct Vec3 *a, const struct Vec3 *b, struct Vec3 *out);
extern int VEC_DotProduct(const struct Vec3 *a, const struct Vec3 *b);
extern int func_01ff8d18(const struct Vec3 *v, struct Vec3 *out);
extern void func_01ffa724(int scale, const struct Vec3 *src, struct Vec3 *dst);
extern int func_ov107_020c8f44(int item, struct Segment *query, int *results);
extern int func_ov107_020ca918(int ent, int actor, int item, int mode, void *dir, int flag);
extern void func_ov158_020cf418(int *state);
extern void func_ov107_020c5af8(int item, int id, int a, void *at);
extern void func_0203c634(int *node, int slot, void *value);
extern int func_ov107_020c9184(int actor, struct Segment *query, void **out);
extern int func_ov107_020c5cfc(int lock, int param, struct HitCommand *req);
extern struct Vec3 data_02041dc8;

void func_ov158_020cefec(int *node)
{
    int *state = (int *)node[1];
    struct Segment query;
    struct Vec3 d;
    struct Vec3 bestDir;
    int results[4];
    void *handle;
    int lock;
    int i;
    int n;
    int nBest = 0x80000001;
    char *found = 0;
    char *list = *(char **)(*state + 4);
    char **it;
    char *e;
    int dot;

    if (state[9] == 0) {
        it = func_01fffd70(list + 0xa8);
        e = (it == 0) ? found : *it;
        while (e != 0) {
            if (((struct Ov158Bits40 *)(e + 0x40))->b1 != 0 && (((struct Ov158HalfByte *)(e + 0x60))->lo & 1) != 0) {
                VEC_Subtract((struct Vec3 *)(e + 0x74), (struct Vec3 *)state[1], &d);
                func_01ff8d18(&d, &d);
                dot = VEC_DotProduct((struct Vec3 *)(state + 5), &d);
                if (dot > 0x400 && dot > nBest) {
                    nBest = dot;
                    bestDir = d;
                    found = e;
                }
            }
            it = func_01fffd8c(list + 0xa8);
            e = (it == 0) ? 0 : *it;
        }
        if (found != 0) {
            state[5] += (bestDir.x - state[5]) / 10;
            state[6] += (bestDir.y - state[6]) / 5;
            state[7] += (bestDir.z - state[7]) / 10;
            func_01ff8d18((struct Vec3 *)(state + 5), (struct Vec3 *)(state + 5));
        }
    }
    func_01ffa724(state[8], (struct Vec3 *)(state + 5), (struct Vec3 *)(state + 2));
    query.origin = *(struct Vec3 *)state[1];
    query.dir = *(struct Vec3 *)(state + 5);
    query.nLength = state[8];
    query.nRadius = 0xe00;

    if (state[9] == 0) {
        n = func_ov107_020c8f44(*(int *)(*state + 0x38c), &query, results);
        i = 0;
        if (n > 0) {
            do {
                if (func_ov107_020ca918(results[i], *state, *(int *)(*state + 0x38c), 1, state + 2, 0) != 0) {
                    func_ov158_020cf418(state);
                    func_ov107_020c5af8(*(int *)(*state + 0x38c), 0x150, 8, (void *)state[1]);
                    func_ov107_020c5af8(*(int *)(*state + 0x38c), 0x150, 7, (void *)state[1]);
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
            req.field10 = (req.field10 & 0xffff0000) | *(u16 *)(*(int *)(*state + 0x38c) + 0x200 + 0x96);
            req.field14 = (req.field14 & 0xffff0000) | (u16)*(int *)(*state + 0x258);
            req.hit18 = handle;
            if ((((struct Ov158Byte8 *)((char *)handle + 8))->lo & 1) != 0
                && func_ov107_020c5cfc(lock, *(int *)(*state + 0x25c), &req) != 0) {
                func_ov158_020cf418(state);
                func_ov107_020c5af8(*(int *)(*state + 0x38c), 0, 0x53, (void *)state[1]);
                *(u8 *)(*state + 0x1c7) = 0;
                func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
                return;
            }
        }
    }

    state[0xa] += state[8];
    if (((struct Ov158Contact *)(*state + 0x17a))->bGrounded == 0
        && ((struct Ov158Contact *)(*state + 0x17a))->bBlocked == 0
        && state[0xa] <= 0x1e000) {
        return;
    }
    func_ov158_020cf418(state);
    func_ov107_020c5af8(*(int *)(*state + 0x38c), 0x150, 7, (void *)state[1]);
    *(u8 *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
