/* Waypoint arrival of the ov243 enemy (x3: ov243/242/243): reads the current 20-byte waypoint
 * (+0x398 table, +0x24 index) -- its +0xc dwell time goes to +0x2c; with luck under the
 * waypoint's +0x10 chance (a 0..99 roll) the actor plays pose 3 and the wait handler 020d08ec
 * takes over; otherwise a dwell of at most 0x100 advances straight to the next waypoint
 * (020d09c8) and a longer one plays pose 0 (looping) under the dwell handler 020d0994. */
struct Waypoint {
    int pad[3];
    int nDwell;
    unsigned int uChance;
};

extern int func_02023eb4(int bound);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int node, int slot, void *cb);
extern void func_ov243_020d4370(void);
extern void func_ov243_020d444c(void);
extern void func_ov243_020d4418(void);

void func_ov243_020d42c0(int node)
{
    int *state = *(int **)(node + 4);
    struct Waypoint *wp = (struct Waypoint *)(*(int *)(*state + 0x398) + state[9] * 0x14);
    state[0xb] = wp->nDwell;
    if ((unsigned int)func_02023eb4(0x64) < wp->uChance) {
        func_ov107_020c9264(*state, 3, 0);
        func_0203c634(node, *(signed char *)(node + 0x20), func_ov243_020d4370);
        return;
    }
    if (state[0xb] <= 0x100) {
        func_0203c634(node, *(signed char *)(node + 0x20), func_ov243_020d444c);
        return;
    }
    func_ov107_020c9264(*state, 0, 1);
    func_0203c634(node, *(signed char *)(node + 0x20), func_ov243_020d4418);
}
