/* func_ov253_020d01c0 -- carry hold tick: the +0x18 speed follows twice the frame step
 * (30 / 15) and the +0x1c timer runs up; past 1.0 bit 1 of the +0x3bc target's +0x60 high byte
 * clears, the target is dropped, pose 7 plays and the node moves to 020d0938. Before that,
 * once the target's +0x18c rider raises flag 0x8000 of its +0x464 word, message
 * data_ov253_020d4964 + 0x14 (kind 6, with the target's +2 id) goes through the actor's +0x24
 * hook, the latch and timer clear, pose 7 plays, the rider is released (020ad838) and the node
 * moves to 020d0344; otherwise the rider is only refreshed (020ad8e0). */
typedef unsigned short u16;
struct htriple { unsigned short a, b, c; };
struct Ov253Rider { char pad[0x464]; unsigned long long flags; };

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov022_020ad838(int target, int a);
extern void func_ov022_020ad8e0(int target, int a);
extern int data_ov253_020d4964;
extern void func_ov253_020d0344(void);
extern void func_ov253_020d0938(void);

void func_ov253_020d01c0(int *node) {
    int *state = (int *)node[1];
    struct htriple msg;
    int rider;

    state[6] = *(int *)(node[0] + 0x2c) * 0x1e / 0xf;
    state[7] += *(int *)(node[0] + 0x2c);
    if (state[7] >= 0x1000) {
        {
            int target = *(int *)(*state + 0x3bc);
            u16 hw = *(u16 *)(target + 0x60);
            *(u16 *)(target + 0x60) = (hw & ~0xff00) |
                (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~2) << 0x18) >> 0x10);
        }
        *(int *)(*state + 0x3bc) = 0;
        func_ov107_020c9264(*state, 7, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov253_020d0938);
        return;
    }
    rider = *(int *)(*(int *)(*state + 0x3bc) + 0x18c);
    if ((((struct Ov253Rider *)rider)->flags & 0x8000ULL) != 0) {
        msg = *(struct htriple *)((char *)&data_ov253_020d4964 + 0x14);
        msg.c = *(u16 *)(*(int *)(*state + 0x3bc) + 2);
        if (*(void **)(*state + 0x24) != 0) {
            (*(void (**)(int, struct htriple *, int))(*state + 0x24))(*state, &msg, 6);
        }
        *((unsigned char *)state + 0x30) = 0;
        state[7] = 0;
        func_ov107_020c9264(*state, 7, 0);
        func_ov022_020ad838(*(int *)(*(int *)(*state + 0x3bc) + 0x18c), 1);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov253_020d0344);
        return;
    }
    func_ov022_020ad8e0(rider, 1);
}
