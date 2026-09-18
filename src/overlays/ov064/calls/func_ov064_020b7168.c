/* Run the per-state handler of every 0x1c8-byte part of this enemy (count at +0x19, array at
 * +0xc, handler table indexed by the part's state byte at +2). When a handler moves a part from
 * state 2 (starting) to state 4 (launched): spawn effect 0xc9 at the part's +0xcc position if the
 * owner's +0x694 bit is set (variant by whether the part's model is in mode 2), and on the local
 * player's side, unless the owner is in state 0x10000, queue reaction 3 with the same mode
 * variant in the owner's +0x47a/+0x47b pair. Codegen: the owner's state is a 64-bit flag word;
 * the test is written as the 64-bit AND truncated to int, which loads only the low word (into r1,
 * the pair's slot, leaving the player index in r0). */
extern void func_02033d0c(int nId, int nSub, int *pPos, int nFlag);            /* Slot_Spawn */
extern int func_02030788(void);                                                /* Session_GetLocalPlayerIndex */
extern void (*data_ov064_020b7394[])(char *group, char *part, void *arg);

typedef struct OwnerFlags694 {
    unsigned char bSpawnEffect : 1;
} OwnerFlags694;

void func_ov064_020b7168(char *group, void *arg)
{
    void (*handler)(char *group, char *part, void *arg);
    char *owner;
    int launching;
    char *part;
    int player;
    int i;
    int state;

    owner = *(char **)(group + 8);
    for (i = 0; i < *(unsigned char *)(group + 0x19); i++) {
        part = *(char **)(group + 0xc) + i * 0x1c8;
        state = *(signed char *)(part + 2);
        if (state != 0) {
            handler = data_ov064_020b7394[state];
            launching = (state == 2);
            handler(group, part, arg);
            if (*(signed char *)(part + 2) == 4 && launching) {
                int variant = (*(int *)(*(int *)(part + 0x138) + 0x3c) != 2);
                if (((OwnerFlags694 *)(owner + 0x694))->bSpawnEffect) {
                    func_02033d0c(0xc9, variant, (int *)(part + 0xcc), 0);
                }
                player = func_02030788();
                if (player == 0 && !(int)(*(unsigned long long *)owner & 0x10000)) {
                    owner[0x47a] = 3;
                    if (*(int *)(*(int *)(part + 0x138) + 0x3c) == 2) {
                        owner[0x47b] = 0;
                    } else {
                        owner[0x47b] = 1;
                    }
                }
            }
        }
    }
}
