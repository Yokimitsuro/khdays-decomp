/* Enter the recoil state of the ov161 enemy (x2: ov161/162), variant of the matched ov163
 * sibling: unless the gate byte at state[0x12] says otherwise, send the 4-byte message copied
 * from the table's second pair through the actor's +0x24 hook, play animation 7, clear the
 * actor's +0x3cc bit 0, zero the +0x24 vector and the +0x58/+0x30 counters and advance to
 * func_ov161_020ce56c. */
extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov161_020ce56c(void);
extern unsigned short data_ov161_020cf278[];
extern int data_02041dc8[];

typedef struct { unsigned short a, b; } Ov161Pair;
typedef struct { int x, y, z; } VecFx32;

void func_ov161_020ce4c4(int *node) {
    int *state = (int *)node[1];
    Ov161Pair buf;
    void (*pfnHook)(int, Ov161Pair *, int);
    Ov161Pair *pMsg;

    if (*(unsigned char *)state[0x12] != 0) {
        return;
    }
    pMsg = &buf;
    buf.b = data_ov161_020cf278[3];
    buf.a = data_ov161_020cf278[2];
    pfnHook = *(void (**)(int, Ov161Pair *, int))(state[0] + 0x24);
    if (pfnHook != 0) {
        (*pfnHook)(state[0], pMsg, 4);
    }
    func_ov107_020c9264(state[0], 7, 1);
    *(int *)(state[0] + 0x3cc) &= ~1;
    *(VecFx32 *)(state + 9) = *(VecFx32 *)data_02041dc8;
    state[0x16] = 0;
    state[0xc] = 0;
    func_0203c634(node, *(signed char *)((int)node + 0x20), func_ov161_020ce56c);
}
