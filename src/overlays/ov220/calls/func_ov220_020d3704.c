/* Guard end of the ov220 enemy: once the +4 item is idle the +0x1c phase advances and the +0x21a
 * stamina is refilled from the +0x218 maximum divided by 2, 3 or 5 (at least 1) according to the
 * phase; then the state ends with sub-state 2. */
typedef unsigned char u8;
typedef short s16;

struct Ov220Actor {
    char pad000[0x1c6];
    signed char bPrevSubState1c6;
    u8 bSubState1c7;
    char pad1c8[0x50];
    s16 nStaminaMax218;
    s16 nStamina21a;
};

extern int func_02020400(int a, int b);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov220_020d3704(int *node)
{
    int *state = (int *)node[1];
    struct Ov220Actor *actor;
    int div;

    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    {
        switch (state[7]) {
        case 0:
            state[7]++;
            div = 2;
            break;
        case 1:
            state[7]++;
            div = 3;
            break;
        default:
            state[7]++;
            div = 5;
            break;
        }
        actor = (struct Ov220Actor *)*state;
        actor->nStamina21a = func_02020400(actor->nStaminaMax218, div);
        actor = (struct Ov220Actor *)*state;
        if (actor->nStamina21a <= 0) {
            actor->nStamina21a = 1;
        }
    }
    ((struct Ov220Actor *)*state)->bSubState1c7 = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
