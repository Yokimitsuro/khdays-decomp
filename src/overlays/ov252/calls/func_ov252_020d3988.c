/* Spawn an ov252 bomb (class 020d3cf8, update 020d3bdc) for `owner` at `pos`: it avoids the
 * other nine live bombs of the +0x774 pair table (skipping slot `slot`): when one lies within 6.0
 * the bomb is moved to the first of the eight ring offsets around its point (6.0 on each axis
 * and diagonal) whose ground, probed 3.125 down from 16.0 up, sits within 0x10. The bomb then
 * rests at height 0 on the owner's +4 transform and records its slot (+0x24) and kind (+0x25).
 * Returns the spawn handle. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 v[8]; } Ring8;
typedef struct { void *a; void *b; void *c; int d; } CollisionHit;
struct Bomb { int owner; char *spawner; Vec3 pos; char pad14[0x10]; u8 slot; u8 kind; };
struct BombPair { int obj; int active; };
struct Spawner { char pad[0x774]; struct BombPair pair[10]; };

extern int func_0203c5c0(int scene, int kind, int size, void *cb, void *cls, struct Bomb **out);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern CollisionHit *func_01fff920(void *collision, Vec3 *origin, Vec3 *direction);
extern void func_0203ca30(void *srt, const Vec3 *v);
extern void func_ov252_020d3bdc(void);
extern void func_ov252_020d3cf8(void);
extern const Vec3 data_02041dc8;

int func_ov252_020d3988(char *self, int owner, Vec3 *pos, signed char slot, u8 kind)
{
    Vec3 p;
    Vec3 d;
    Vec3 a;
    Vec3 b;
    struct Bomb *bomb;
    int handle;
    signed char i;
    signed char j;
    int item;
    int depth;
    int diff;

    handle = func_0203c5c0(*(int *)(self + 0x3c), 0x64, 0x28, func_ov252_020d3bdc, func_ov252_020d3cf8, &bomb);
    bomb->spawner = self;
    bomb->owner = owner;
    bomb->pos = *pos;
    p = bomb->pos;
    i = 0;
    {
    Ring8 cur;
    Ring8 ring = { { { 0x6000, 0, 0 }, { -0x6000, 0, 0 }, { 0x6000, 0, 0x6000 }, { 0x6000, 0, -0x6000 },
                     { -0x6000, 0, 0x6000 }, { -0x6000, 0, -0x6000 }, { 0, 0, 0x6000 }, { 0, 0, -0x6000 } } };
    Vec3 zero = data_02041dc8;
    Vec3 down = { 0, -0x32000, 0 };

    for (; i < 10; i++) {
        if (i == slot) {
            continue;
        }
        if (((struct Spawner *)self)->pair[i].active == 0) {
            continue;
        }
        VEC_Subtract((Vec3 *)(((struct Spawner *)self)->pair[i].obj + 0x14), &p, &d);
        if (func_01ff8d18(&d, &d) >= 0x6000) {
            continue;
        }
        {
            cur = ring;
            for (j = 0; j < 8; j++) {
                a = zero;
                item = *(int *)(bomb->spawner + 4);
                b = down;
                VEC_Add(&p, &cur.v[j], &a);
                a.y = 0x10000;
                {
                    CollisionHit *hit = func_01fff920(*(void **)(item + 0x7c), &a, &b);

                    if (hit != 0 && hit->c == 0) {
                        depth = (int)(((long long)hit->d * b.y) >> 27);
                        if (depth < 0) {
                            depth = -depth;
                        }
                        diff = depth - a.y;
                        if (diff < 0) {
                            diff = -diff;
                        }
                        if (diff <= 0x10) {
                            a.y = 0;
                            bomb->pos = a;
                            i = 0xa;
                            break;
                        }
                    }
                }
            }
        }
    }
    }
    bomb->pos.y = 0;
    func_0203ca30((void *)(bomb->owner + 4), &bomb->pos);
    bomb->slot = slot;
    bomb->kind = kind;
    return handle;
}
