/* Engage entry of the ov116 enemy (byte-identical twin of ov115 020ce5dc). Looks for a target in reach:
 * without one the state ends with sub-state 2. Otherwise the actor plays animation 2, the +0x48
 * timer and +0x84 phase reset, a 6-byte message copied from the overlay's template (+4 of the
 * table block) carries the actor's and the target's +2 ids on channel 4, reaction 0x114 mode 4
 * fires at the +8 position and the tick hands off to the engage state. */
typedef unsigned char u8;
typedef unsigned short u16;

struct Pair { u16 self, kind; };
struct Msg6 { struct Pair id; u16 target; };

/* data_ov116_020d27b0: the two impact reaction pairs, then the engage message template.
 * The template is copied as a typed struct member (read through a cast pointer the copy is
 * scheduled differently). */
struct Ov116Templates { u8 impactPairs[4]; struct Msg6 engageMsg; };

extern int func_ov107_020cab14(int actor, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_02031384(int channel, void *msg, int len);
extern void func_ov107_020c5af8(int actor, int a, int id, void *at);
extern const struct Ov116Templates data_ov116_020d27b0;
extern void func_ov116_020d22f0(int *node);

void func_ov116_020d221c(int *node)
{
    int *state = (int *)node[1];
    struct Msg6 msg;

    state[3] = func_ov107_020cab14(*state, 0);
    if (state[3] == 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    func_ov107_020c9264(*state, 2, 0);
    state[0x12] = 0;
    *(u8 *)(state + 0x21) = 0;
    msg = data_ov116_020d27b0.engageMsg;
    msg.id.self = *(u16 *)(*state + 2);
    msg.target = *(u16 *)(state[3] + 2);
    func_02031384(4, &msg, 6);
    func_ov107_020c5af8(*state, 0x114, 4, (void *)state[2]);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov116_020d22f0);
}
