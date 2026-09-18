/* Begin the ov191 enemy's "pick target" state (x3: ov191/192/193): plays pose 3, clears the
 * +0x2c/+0x38 counters, sets the turn rate (+0x30) to 30x the node's +0x2c speed over 5, sends
 * the canned {0,5} event to the notify hook, gathers the owner's +0xa8 actor list (up to four
 * entries, the count kept as a byte), and with none goes to sub-state 2; otherwise picks one at
 * random as the target (+0x18), faces its +0x190 anchor from the +8 position, re-sets the turn
 * rate and advances to the chase handler (020d1370).
 * The candidate array is a block-scoped `int found[4] = {0, 0, 0, 0}` opened after the notify
 * call: the initialiser is what zeroes it through one base register, at that position. */
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned short a, b; } Pair;

extern void func_ov107_020c9264(int obj, int anim, int flag);
extern int *func_01fffd70(void *list);
extern int *func_01fffd8c(void *list);
extern int func_02023eb4(int bound);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void func_0203c634(int node, int slot, void *cb);
extern Pair data_ov191_020d2d70;
extern void func_ov191_020d1370(void);

void func_ov191_020d11d4(int node)
{
    int *state = *(int **)(node + 4);
    Pair p;
    int found[4];
    Vec3 d;
    signed char n = 0;
    int owner;
    int *pNode;
    int actor;
    void (*cb)(int owner, Pair *p, int n);

    func_ov107_020c9264(*state, 3, 0);
    state[0xb] = 0;
    *(unsigned char *)(state + 0xe) = 0;
    state[0xc] = *(int *)(*(int *)node + 0x2c) * 30 / 5;
    {
        Pair *pp = &p;
        pp->b = data_ov191_020d2d70.b;
        pp->a = data_ov191_020d2d70.a;
        cb = *(void (**)(int, Pair *, int))(*state + 0x24);
        if (cb != 0) {
            cb(*state, pp, 4);
        }
    }
    {
        int found[4] = {0, 0, 0, 0};
        owner = *(int *)(*state + 4);
        pNode = func_01fffd70((void *)(owner + 0xa8));
        actor = pNode == 0 ? 0 : *pNode;
        while (actor != 0) {
            found[n] = actor;
            n = n + 1;
            pNode = func_01fffd8c((void *)(owner + 0xa8));
            actor = pNode == 0 ? 0 : *pNode;
        }
        if (n == 0) {
            *(unsigned char *)(*state + 0x1c7) = 2;
            func_0203c634(node, *(signed char *)(node + 0x20), 0);
            return;
        }
        state[6] = found[func_02023eb4(n)];
        VEC_Subtract((Vec3 *)(state[6] + 0x190), (Vec3 *)state[2], &d);
        state[5] = func_020050b4(d.x, d.z);
        state[0xc] = *(int *)(*(int *)node + 0x2c) * 30 / 5;
        func_0203c634(node, *(signed char *)(node + 0x20), func_ov191_020d1370);
    }
}
