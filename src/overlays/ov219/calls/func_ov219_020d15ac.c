/* Guard end of the ov219 enemy (and its byte-identical twin): once the +4 item is idle, if the
 * previous sub-state was 3 and the +0x21a stamina is spent, the +0x18 phase advances and the
 * stamina is refilled from the +0x218 maximum divided by 2, 3 or 5 (at least 1) according to the
 * phase; then the state ends with sub-state 2. */
typedef unsigned char u8;
typedef short s16;

struct Ov219Actor {
    char pad000[0x1c6];
    signed char bPrevSubState1c6;
    u8 bSubState1c7;
    char pad1c8[0x50];
    s16 nStaminaMax218;
    s16 nStamina21a;
};

extern int func_02020400(int a, int b);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov219_020d15ac(int *node)
{
    int *state = (int *)node[1];
    struct Ov219Actor *actor;
    int div;

    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    actor = (struct Ov219Actor *)*state;
    if (actor->bPrevSubState1c6 == 3 && actor->nStamina21a == 0) {
        switch (state[6]) {
        case 0:
            state[6]++;
            div = 2;
            break;
        case 1:
            state[6]++;
            div = 3;
            break;
        default:
            state[6]++;
            div = 5;
            break;
        }
        actor = (struct Ov219Actor *)*state;
        actor->nStamina21a = func_02020400(actor->nStaminaMax218, div);
        actor = (struct Ov219Actor *)*state;
        if (actor->nStamina21a <= 0) {
            actor->nStamina21a = 1;
        }
    }
    ((struct Ov219Actor *)*state)->bSubState1c7 = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
