/* Summon wind-up tick: until the +9 one-shot fires, the +0x1c timer accumulates the frame rate and
 * at 0x5555 the start note (data_ov277_020d36bc + 0x20) goes out through the actor's +0x24 hook.
 * Once the actor's +0x420 level reaches 4 the done note (+0x1c) goes out and the next move is 5;
 * otherwise, once the +0x30 flag byte clears, the next note (+0x18) goes out, the actor plays
 * pose 8, the +0x14 wave counter, the one-shot and the timer reset and the node moves to the
 * summon tick 020d061c. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char s8;
struct Level { int n : 4; };

struct Ov244Actor {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov244Actor *self, void *msg, int size);
};

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern const u16 data_ov277_020d36bc[];
extern void func_ov277_020d05b4(void);

void func_ov277_020d044c(int *node)
{
    int *state = (int *)node[1];
    u16 noteStart[2];
    u16 noteDone[2];
    u16 noteNext[2];
    u16 *pp;

    if (*((u8 *)state + 9) == 0) {
        state[7] += *(int *)(node[0] + 0x2c);
        if (state[7] >= 0x5555) {
            pp = noteStart;
            pp[1] = data_ov277_020d36bc[0x11];
            pp[0] = data_ov277_020d36bc[0x10];
            if (((struct Ov244Actor *)*state)->pfnMessage != 0) {
                ((struct Ov244Actor *)*state)->pfnMessage((struct Ov244Actor *)*state, pp, 4);
            }
            *((u8 *)state + 9) = 1;
        }
    }
    if (((struct Level *)(*state + 0x420))->n >= 4) {
        pp = noteDone;
        pp[1] = data_ov277_020d36bc[0xf];
        pp[0] = data_ov277_020d36bc[0xe];
        if (((struct Ov244Actor *)*state)->pfnMessage != 0) {
            ((struct Ov244Actor *)*state)->pfnMessage((struct Ov244Actor *)*state, pp, 4);
        }
        *(s8 *)(*state + 0x1c7) = 5;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (*(u8 *)state[0xc] != 0) {
        return;
    }
    pp = noteNext;
    pp[1] = data_ov277_020d36bc[0xd];
    pp[0] = data_ov277_020d36bc[0xc];
    if (((struct Ov244Actor *)*state)->pfnMessage != 0) {
        ((struct Ov244Actor *)*state)->pfnMessage((struct Ov244Actor *)*state, pp, 4);
    }
    func_ov107_020c9264(*state, 8, 0);
    *(short *)((u8 *)state + 0x14) = 0;
    *((u8 *)state + 9) = 0;
    state[7] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov277_020d05b4);
}
