/* Volley tick of the ov244 enemy. Once the owner's +0x420 phase reaches 4 the overlay's end message
 * goes to the owner's +0x24 hook and sub-state 5 follows. Otherwise the +0x1c clock runs up at the
 * owner's rate; at 0.58 (once, +9) up to counts[+0x14] of the six +0x404 parts that are not busy
 * are fanned out around the +0x3b0 muzzle: each takes the muzzle's orientation times the overlay's
 * base turn, spun about the up axis by an alternating angle that widens every second part
 * (020cd3f0), and reaction 0x113 mode 0xe fires at the muzzle. After 0.33, once the +0x30 flag
 * clears, the +0x14 volley count advances: the fourth volley sends the "done" message, plays pose 9
 * and hands over to 020d08a4; any other sends the "next" message, resets the clock and plays pose 8. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;
typedef struct { u16 id; u16 arg; } Msg4;
typedef struct { signed char c[4]; } Counts;
struct Phase { int n : 4; };
struct Hw60 { u16 lo : 8, hi : 8; };

struct VolleyTable {
    char pad00[8];
    Msg4 msgDone;       /* +0x08 */
    char pad0c[4];
    Msg4 msgNext;       /* +0x10 */
    Counts counts;      /* +0x14 */
    char pad18[0x14];
    Msg4 msgEnd;        /* +0x2c */
};

typedef void (*MsgHook)(int owner, Msg4 *msg, int size);

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_0202ef54(Quat *out, const Quat *a, const Quat *b);
extern int func_02020400(int num, int den);
extern void func_0202f188(Quat *q, const Vec3 *axis, int angle);
extern void func_ov244_020cd3f0(int part, Vec3 *at, Quat *q);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov107_020c9264(int owner, int pose, int loop);
extern void func_ov244_020d090c(void);
extern const struct VolleyTable data_ov244_020d3724;
extern const Quat data_ov244_020d3764;
extern const Vec3 data_02042264;

void func_ov244_020d061c(int *node)
{
    int *state = (int *)node[1];
    Quat q;
    Quat rot;
    Quat spin;
    Quat base;
    Counts counts = data_ov244_020d3724.counts;
    long i;
    int k;
    int sign;

    if (((struct Phase *)(*state + 0x420))->n >= 4) {
        Msg4 msg = data_ov244_020d3724.msgEnd;

        if (*(MsgHook *)(*state + 0x24) != 0) {
            (*(MsgHook *)(*state + 0x24))(*state, &msg, 4);
        }
        *(unsigned char *)(*state + 0x1c7) = 5;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[7] += *(int *)(node[0] + 0x2c);
    if (*((unsigned char *)state + 9) == 0 && state[7] >= 0x2555) {
        *((unsigned char *)state + 9) = 1;
        base = data_ov244_020d3764;
        k = 0;
        for (i = 0; i < 6; i++) {
            if ((((struct Hw60 *)(((int *)*(int *)(*state + 0x404))[i] + 0x60))->lo & 1) != 0) {
                continue;
            }
            q = base;
            sign = (k & 1) ? -1 : 1;
            func_0202ef54(&rot, (Quat *)(*(int *)(*state + 0x3b0) + 4), &q);
            func_0202f188(&spin, &data_02042264,
                          sign * func_02020400(counts.c[*(short *)(state + 5)] * 0x3244, k / 2 + 1) >> 5);
            func_0202ef54(&spin, &spin, &rot);
            func_ov244_020cd3f0(((int *)*(int *)(*state + 0x404))[i], (Vec3 *)(*(int *)(*state + 0x3b0) + 0x14), &spin);
            if (++k == counts.c[*(short *)(state + 5)]) {
                break;
            }
        }
        func_ov107_020c5af8(*state, 0x113, 0xe, (void *)(*(int *)(*state + 0x3b0) + 0x14));
    }
    if (state[7] <= 0x555) {
        return;
    }
    if (*(unsigned char *)state[0xc] != 0) {
        return;
    }
    *(short *)(state + 5) += 1;
    if (*(short *)(state + 5) == 4) {
        u16 note[2];
        u16 *pp;

        pp = note;
        pp[1] = data_ov244_020d3724.msgDone.arg;
        pp[0] = data_ov244_020d3724.msgDone.id;
        if (*(MsgHook *)(*state + 0x24) != 0) {
            (*(MsgHook *)(*state + 0x24))(*state, (Msg4 *)pp, 4);
        }
        func_ov107_020c9264(*state, 9, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov244_020d090c);
        return;
    }
    {
        u16 note[2];
        u16 *pp;

        pp = note;
        pp[1] = data_ov244_020d3724.msgNext.arg;
        pp[0] = data_ov244_020d3724.msgNext.id;
        if (*(MsgHook *)(*state + 0x24) != 0) {
            (*(MsgHook *)(*state + 0x24))(*state, (Msg4 *)pp, 4);
        }
    }
    state[7] = 0;
    *((unsigned char *)state + 9) = 0;
    func_ov107_020c9264(*state, 8, 0);
}
