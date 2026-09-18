/* Leap tick of the ov169 enemy (and its byte-identical twins). A hit on the sweep ends the state
 * (sub-state 0). While the +0x30 clock is within the +0x34 flight time the +0x10 height follows
 * a half-sine arc: the +0x3c drop plus 0x1800 scaled by the change of sin(clock/time * pi) is
 * added to the +0x40 shadow height, the +0x38 remembers the sine and the clock advances thirty
 * frame-times; past it the height falls by (frame-time * 0x100) / 136. The step from the +0x24
 * origin to the +8 position is cast against the scene: a ray hit clips the step, lands the actor
 * there (020c5c54), publishes the position to the +0x38c item with mode 7 plus reaction 0x13f
 * mode 7, sets bit 7 and clears bit 0 of the +0x60 flag high byte, clears bit 0 of the +0x388
 * item's +8 byte, zeroes the +0x44 timer and hands off to the landing state. Without a ray hit,
 * a blocked sphere cast (0x300) or an item with any of bits 1/3 set at +0x1c4 publishes mode 1
 * (the reaction only when those bits are clear) and ends with sub-state 0. */
typedef unsigned char u8;

struct Vecx32 { int x, y, z; };
struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned f : 8; };
struct CastHit { int f0; int f4; int nBlocked; int nFraction; };

extern int func_ov169_020ce424(int *state, void *sphere, void *push);
extern void func_0203c634(int *node, int slot, void *cb);
extern int FX_Inv(int a, int b);
extern void VEC_Subtract(void *a, void *b, void *d);
extern struct CastHit *func_01fff920(void *world, void *from, void *step);
extern void func_01ffd144(int scale, void *v, void *d);
extern void VEC_Add(void *a, void *b, void *d);
extern void func_ov107_020c5c54(int actor, void *at);
extern void func_ov107_020c0b90(void *item, int a, struct Vecx32 v, int b);
extern void func_ov107_020c5af8(int actor, int a, int id, void *at);
extern struct CastHit *func_01fff8e8(void *world, void *from, void *step, int radius, void *z);
extern const short data_0203d210[];
extern void func_ov169_020ceda8(int *node);

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov169_020cea4c(int *node)
{
    int *state = (int *)node[1];
    struct Vecx32 step;
    struct Vecx32 at;
    unsigned short *hw;
    unsigned int h;
    int scene;
    int time;
    int sine;
    int idx;
    struct CastHit *hit;

    scene = *(int *)(*state + 4);
    if (func_ov169_020ce424(state, (void *)(*state + 0x74), 0) != 0) {
        *(u8 *)(*state + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    time = state[0xd];
    if (time <= 0 || state[0xc] > time) {
        state[4] += (*(int *)(*node + 0x2c) * -0x100) / 136;
    } else {
        if (time != 0) {
            /* guard written positively: the other way round the scheduler fills the umull slot
             * with the rounding add (adds before mla) */
            idx = (unsigned short)((0x28BE60DB9391LL * FX_Mul(FX_Inv(state[0xc], time), 0x3244) + 0x80000000000LL) >> 44);   /* FX_RAD_TO_IDX */
            sine = data_0203d210[(idx >> 4) << 1];                                                                     /* FX_SinIdx */
        } else {
            sine = 0;
        }
        state[4] = state[0x10] + FX_Mul(state[0xf] + 0x1800, sine - state[0xe]);
        state[0xe] = sine;
        state[0xc] = *(int *)(*node + 0x2c) * 0x1e + state[0xc];
    }
    VEC_Subtract((void *)state[2], (void *)(state + 9), &step);
    *(struct Vecx32 *)(state + 9) = *(struct Vecx32 *)state[2];
    hit = func_01fff920(*(void **)(scene + 0x7c), (void *)state[2], &step);
    if (hit != 0) {
        func_01ffd144(hit->nFraction, &step, &step);
        VEC_Add(&step, (void *)state[2], &at);
        func_ov107_020c5c54(*state, &at);
        func_ov107_020c0b90(*(void **)(*state + 0x38c), 7, *(struct Vecx32 *)state[2], 0);
        func_ov107_020c5af8(*state, 0x13f, 7, (void *)state[2]);
        hw = (unsigned short *)(*state + 0x60);
        h = *hw;
        /* hw60.hi |= 0x80 -- explicit-shift form (bitfield |= adds a redundant mask) */
        *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0x80) << 0x18) >> 0x10);
        ((struct hw60 *)(*state + 0x60))->hi &= ~1;
        ((struct b8 *)(*(int *)(*state + 0x388) + 8))->f &= ~1;
        state[0x11] = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov169_020ceda8);
        return;
    }
    hit = func_01fff8e8(*(void **)(scene + 0x7c), (void *)state[2], &step, 0x300, 0);
    if (!(hit != 0 && hit->nBlocked == 0) && (*(u8 *)(*(int *)(*state + 0x38c) + 0x1c4) & 0xa) == 0) {
        return;
    }
    func_ov107_020c0b90(*(void **)(*state + 0x38c), 1, *(struct Vecx32 *)state[2], 0);
    if ((*(u8 *)(*(int *)(*state + 0x38c) + 0x1c4) & 0xa) == 0) {
        func_ov107_020c5af8(*state, 0x13f, 7, (void *)state[2]);
    }
    *(u8 *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
