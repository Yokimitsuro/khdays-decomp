/*
 * func_ov288_020d3b50 -- Ov287_Actor_HandleEvent.
 *
 * The actor class event handler installed in the +0x1c slot by func_ov288_020d3844, shared
 * with ov288 and ov289. Kind 0 runs one of two ov002 hold callbacks when the actor is holding
 * something at +0x390. Kind 5 dispatches on the sub-opcode:
 *   0, 1  start the slot's subitem through ov107::020c08cc at unit weight and keep the handle
 *         in the same slot; 0 passes the blend byte, 1 passes zero
 *   2     ignored
 *   3     decode three big-endian 24-bit fixed-point values from the payload, scale the blend
 *         byte by the actor's +0x220 factor into the first or second colour byte depending on
 *         bit 2 of the global at 0204c240, and forward both to ov002
 *   4     push a two-bit sub-state and the full seven-bit value into the first subitem and
 *         refresh it
 * Every path then forwards the event to the ov107 base handler.
 *
 * Ghidra: Ov287_Actor_HandleEvent(Ov287Actor *pActor, ActorEventMsg *pMsg, uint uParam), types
 * /khdays/ActorEventMsg, /khdays/ActorSubitemSlot, /khdays/Fx24Word and /khdays/ActorEventWork.
 *
 * Byte-exact codegen notes (mwccarm 3.0/139):
 *  - The three sub-opcode-3 scratch words, the colour bytes and the decoded vector are one
 *    stack struct, not three separate locals. Declaration order does not move locals here --
 *    all 120 permutations compile identically -- so the original's frame layout of scratch at
 *    +8, colour at +0x14 and vector at +0x1c is only reachable by making them one object.
 *  - The colour bytes are cleared through a pointer. Clearing them as array elements makes
 *    mwcc address them off sp; going through a pointer produces the original's single
 *    `add r2, sp, #0x14` and six offsets from it.
 *  - Each payload triple loads into three named temporaries first. Assigning straight from the
 *    packet keeps mwcc's load and store paired one byte at a time, because two u8 lvalues may
 *    alias; the temporaries let it batch three loads then three stores as the original does.
 *    The store order within a triple is low, high, middle -- that is what fixes the registers
 *    to r3, r2, r1 in the original's order.
 *  - case 1 is written before case 0 because the original lays its body out first.
 *  - func_0203c7ac takes two arguments, not four. Declaring the extra two makes mwcc reload
 *    r2 and r3 after the preceding call; the original just leaves them where they were.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct ActorSubitemSlot {
    void *pSubitem;
    void *pResult;
};

struct Actor {
    char pad000[4];
    void *pNode004;
    char pad008[0x34];
    void *pAnimSet03c;
    char pad040[0x10];
    int mode050;
    char pad054[0x1cc];
    int blendScale220;
    char pad224[0x160];
    void *pSubitem384;
    char pad388[8];
    int held390;
    char pad394[0x2c];
    struct ActorSubitemSlot slots3c0[8];
};

struct ActorEventMsg {
    char pad000[2];
    u8 kind;
    u8 sub;
    u8 arg;
    u8 payload0;
    u8 payload1;
    u8 payload2;
    u8 payload3;
    u8 payload4;
    u8 payload5;
    u8 payload6;
    u8 payload7;
    u8 payload8;
    char pad00e[0x16];
    u8 flag24;
};

/* one payload value: three bytes laid into the top of a word, then >>8 to sign-extend 24 bits */
union Fx24Word {
    int w;
    u8 b[4];
};

struct ActorEventWork {
    union Fx24Word scratch[3];
    u8 colour[6];
    int vec[3];
};

extern void func_ov002_02076b68(int held);
extern void func_ov002_02076b48(int held);
extern void *func_ov107_020c08cc(void *animSet, void *subitem, int mode, int blend,
                                 int weight, void *payload);
extern int func_ov002_02072754(void *scene);
extern void func_ov002_02077cec(u8 *colour, u16 id, int *vec);
extern void func_0203b9fc(void *subitem, int channel, int value, u8 on);
extern void func_0203c7ac(void *subitem, int channel);
extern void func_ov107_020c7500(struct Actor *actor, struct ActorEventMsg *msg, u32 param);

extern u8 data_0204c240;

void func_ov288_020d3b50(struct Actor *actor, struct ActorEventMsg *msg, u32 param)
{
    struct ActorEventWork w;
    void *node;
    u8 *colour;
    int held;
    int v;
    u8 on;

    if (msg->kind == 0) {
        held = actor->held390;
        if (held != 0) {
            if (msg->flag24 != 0) {
                func_ov002_02076b68(held);
            } else {
                func_ov002_02076b48(held);
            }
        }
    } else if (msg->kind == 5) {
        switch (msg->sub) {
        case 1:
            actor->slots3c0[msg->sub].pResult =
                func_ov107_020c08cc(actor->pAnimSet03c, actor->slots3c0[msg->sub].pSubitem,
                                    5, 0, 0x1000, &msg->payload0);
            break;
        case 0:
            actor->slots3c0[msg->sub].pResult =
                func_ov107_020c08cc(actor->pAnimSet03c, actor->slots3c0[msg->sub].pSubitem,
                                    5, msg->arg, 0x1000, &msg->payload0);
            break;
        case 2:
            break;
        case 3:
            node = actor->pNode004;
            colour = w.colour;
            colour[0] = 0;
            colour[1] = 0;
            colour[2] = 0;
            colour[3] = 0;
            colour[4] = 0;
            colour[5] = 0;
            v = (u8)(((long long)(msg->arg * actor->blendScale220)) >> 12);
            if (data_0204c240 & 4) {
                w.colour[0] = (u8)v;
            } else {
                w.colour[1] = (u8)v;
            }
            {
                u8 hi = msg->payload0;
                u8 mid = msg->payload1;
                u8 lo = msg->payload2;
                w.scratch[0].b[1] = lo;
                w.scratch[0].b[3] = hi;
                w.scratch[0].b[2] = mid;
            }
            w.vec[0] = w.scratch[0].w >> 8;
            {
                u8 hi = msg->payload3;
                u8 mid = msg->payload4;
                u8 lo = msg->payload5;
                w.scratch[1].b[1] = lo;
                w.scratch[1].b[3] = hi;
                w.scratch[1].b[2] = mid;
            }
            w.vec[1] = w.scratch[1].w >> 8;
            {
                u8 hi = msg->payload6;
                u8 mid = msg->payload7;
                u8 lo = msg->payload8;
                w.scratch[2].b[1] = lo;
                w.scratch[2].b[3] = hi;
                w.scratch[2].b[2] = mid;
            }
            w.vec[2] = w.scratch[2].w >> 8;
            func_ov002_02077cec(w.colour,
                                func_ov002_02072754(*(void **)((char *)node + 0x78)), w.vec);
            break;
        case 4:
            if (actor->mode050 == 2) {
                v = msg->arg & 0x7f;
                on = (u8)((msg->arg & 0x80) ? 1 : 0);
                func_0203b9fc(actor->pSubitem384, 0, (short)(v % 4), on);
                func_0203b9fc(actor->pSubitem384, 2, v, on);
                func_0203c7ac(actor->pSubitem384, 0);
            }
            break;
        }
    }
    func_ov107_020c7500(actor, msg, param);
}
