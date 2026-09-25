/* Run the per-state handler of every 0x1c8-byte part of this enemy (count at +0x19, array at
 * +0xc, handler table by the part's state byte at +2). State 2 is special: while the group is
 * in mode 1 the parts are steered by Ov081_SteerPart, otherwise the shared handler runs and
 * the first part that comes out launched (state 4) spawns effect 0xc7 at its +0xcc position if
 * the owner's +0x694 bit is set and, on the local player's side, queues reaction 3/0 on the
 * owner unless it is in state 0x10000. The owner's state is a 64-bit flag word: the test masks
 * it as a long long and truncates, which loads only the low word (into r1, keeping the player
 * index in r0), as in ov031 020b453c and ov045 020b4968. */
typedef unsigned char u8;

typedef struct OwnerFlags694 {
    u8 bSpawnEffect : 1;
} OwnerFlags694;

extern void func_ov081_020b90d4(char *group, char *part, void *arg);            /* Ov081_SteerPart */
extern void func_ov022_020916e8(char *group, char *part, void *arg);
extern void func_02033d0c(int nId, int nSub, int *pPos, int nFlag);            /* Slot_Spawn */
extern int func_02030788(void);                                                /* Session_GetLocalPlayerIndex */
extern void (*data_ov081_020b9634[])(char *group, char *part, void *arg);

void func_ov081_020b8f74(char *group, void *arg)
{
    int state;
    char *part;
    int launched;
    char *owner;
    int i;

    owner = *(char **)(group + 8);
    launched = 0;
    for (i = 0; i < *(u8 *)(group + 0x19); i++) {
        part = *(char **)(group + 0xc) + i * 0x1c8;
        state = *(signed char *)(part + 2);
        if (state == 0) {
            continue;
        }
        if (state != 2) {
            data_ov081_020b9634[state](group, part, arg);
        } else if (*(int *)group == 1) {
            func_ov081_020b90d4(group, part, arg);
        } else {
            func_ov022_020916e8(group, part, arg);
            if (*(signed char *)(part + 2) == 4 && launched == 0) {
                if (((OwnerFlags694 *)(owner + 0x694))->bSpawnEffect) {
                    func_02033d0c(0xc7, 0, (int *)(part + 0xcc), 0);
                }
                launched = 1;
                if (func_02030788() == 0 && (int)(*(long long *)owner & 0x10000) == 0) {
                    owner[0x47a] = 3;
                    owner[0x47b] = 0;
                }
            }
        }
    }
}
