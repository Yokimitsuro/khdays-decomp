/* Ground drop tick of the ov160 enemy. In owner mode 1 the +0x28 radius grows by the owner's
 * rate and, up to 0xa00, the entities inside 2.0 of the +0x10 anchor are swept: each one whose
 * +0x1b4 slot bit is still clear in the +0x30 hit mask is tested along the zero vector (flag
 * 0x200) and, once accepted, fires reaction 0x151 mode 8 at the anchor, is grabbed into +0x38
 * (its +0x18c body, started with ov022 ad8e0 1) if none is held yet, and marks its bit. Then,
 * unless already done (+0x34), a held body carrying flag bit 15 of its +0x464 pair is pulled:
 * its +0x20 object to the owner's +0xb0 point (0202b450), its +0x4ec attachment there too
 * (+0x190, c5c54, its +0xc hook with 0 when +0x40 bit 1 is set), the body is released, the
 * owner placed at (0.5, 5.0, 0) and the overlay's 14-byte message (data_ov160_020cf7b4) with
 * the object's +0xa8 point lifted 1.0 goes to the owner's +0x24 hook; +0x34 is then set. The
 * state ends once the +0xc sub-object goes idle (+0xad). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;
typedef struct { u8 hi, mid, lo; } Fx24;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int nRadius; } Sphere;

typedef struct {
    u16 id;             /* +0x0 */
    u8 kind;            /* +0x2 */
    u8 cmd;             /* +0x3 */
    u8 flag;            /* +0x4 */
    Fx24 pos[3];        /* +0x5 */
} PosMsg;

struct Ov160Flags464 { char pad[0x464]; unsigned long long flags; };
struct Ov160Bits40 { int b0 : 1, b1 : 1; };

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

extern int func_ov107_020c8eb8(int owner, Sphere *query, int *results);
extern int func_ov107_020ca918(int ent, int owner, int aux, int mode, const Vec3 *dir, int flag);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov022_020ad8e0(int body, int a);
extern void func_0202b450(int object, Vec3 *at);
extern void func_ov107_020c5c54(int ent, Vec3 *at);
extern void func_0203c640(int *node);
extern const Vec3 data_02041dc8;
extern const PosMsg data_ov160_020cf7b4;

void func_ov160_020ce834(int *node)
{
    int *state = (int *)node[1];
    int results[4];
    Sphere query;
    PosMsg msg;
    Vec3 raw;
    FxVec vContact;
    long i;
    long n;
    int e;

    if (*(int *)(*state + 0x50) == 1) {
        state[0xa] += *(int *)(node[0] + 0x2c);
        if (state[0xa] <= 0xa00) {
            query.pos = *(Vec3 *)(state + 4);
            query.nRadius = 0x2000;
            n = func_ov107_020c8eb8(*state, &query, results);
            for (i = 0; i < n; i++) {
                if (((*(u8 *)((char *)state + 0x30) >> *(u8 *)(results[i] + 0x1b4)) & 1) == 0
                    && func_ov107_020ca918(results[i], *state, *state, 0, &data_02041dc8, 0x200) != 0) {
                    func_ov107_020c5af8(*state, 0x151, 8, state + 4);
                    if (state[0xe] == 0) {
                        state[0xe] = *(int *)(results[i] + 0x18c);
                        if (state[0xe] != 0) {
                            func_ov022_020ad8e0(state[0xe], 1);
                        }
                    }
                    *(u8 *)((char *)state + 0x30) |= 1 << *(u8 *)(results[i] + 0x1b4);
                }
            }
        }
    }
    if (state[0xd] == 0 && state[0xe] != 0 && (((struct Ov160Flags464 *)state[0xe])->flags & 0x8000) != 0) {
        func_0202b450(*(int *)(state[0xe] + 0x20), (Vec3 *)(*state + 0xb0));
        e = *(int *)(state[0xe] + 0x4ec);
        if (e != 0) {
            *(Vec3 *)(e + 0x190) = *(Vec3 *)(*state + 0xb0);
            func_ov107_020c5c54(e, (Vec3 *)(e + 0x190));
            e = *(int *)(state[0xe] + 0x4ec);
            if (((struct Ov160Bits40 *)(e + 0x40))->b1 != 0 && *(void (**)(int, int))(e + 0xc) != 0) {
                (*(void (**)(int, int))(e + 0xc))(e, 0);
            }
        }
        func_ov022_020ad8e0(state[0xe], 0);
        msg = data_ov160_020cf7b4;
        raw.x = 0x2000;
        raw.y = 0x5000;
        raw.z = 0;
        func_ov107_020c5c54(*state, &raw);
        raw = *(Vec3 *)(*(int *)(state[0xe] + 0x20) + 0xa8);
        raw.y += 0x1000;
        vContact.x = *(Fx32 *)&raw.x;
        PackFx24(&msg.pos[0], vContact.x.value);
        vContact.y = *(Fx32 *)&raw.y;
        PackFx24(&msg.pos[1], vContact.y.value);
        vContact.z = *(Fx32 *)&raw.z;
        PackFx24(&msg.pos[2], vContact.z.value);
        if (*(void (**)(int, PosMsg *, int))(*state + 0x24) != 0) {
            (*(void (**)(int, PosMsg *, int))(*state + 0x24))(*state, &msg, 0xe);
        }
        state[0xd] = 1;
    }
    if (*(u8 *)(state[3] + 0xad) != 0) {
        return;
    }
    func_0203c640(node);
}
