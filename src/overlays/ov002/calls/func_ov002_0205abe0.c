/* Push one panel slot's state.
 *
 * Forwards the slot and state to the slot bookkeeping, re-pushes the node's own
 * kind together with the caller's value, and invokes the node callback. Only
 * then, and only when the state is 0 or lies between 3 and 6, the node's value
 * and kind are mirrored onto the widget the context holds for tag 2.
 *
 * nState is a state index with ranges, not a flag -- which is why the caller
 * has to select it between two named constants rather than a literal 0 and 1.
 *
 * Two codegen notes. The two out-of-range tests are explicit returns, so the
 * ROM predicates the epilogue instead of branching to a shared tail. And the
 * tag-2 handle is fetched in its own statement: left inside the argument list
 * it is evaluated after the node loads, and the ROM does it first.
 */
typedef unsigned char u8;

typedef struct {
    u8 pad0000[2];
    short nValue;           /* +0x02 */
    short nKind;            /* +0x04 */
} Ov002TagTrackerNode;

typedef struct {
    u8 pad0000[0x620];
    Ov002TagTrackerNode *aNodes[8];   /* +0x620, indexed by slot */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern void func_ov002_0205abb8(int nSlot, int nState);
extern void func_ov002_02053578(Ov002TagTrackerNode *pNode, short nValue,
                                short nKind);
extern void func_ov002_020535a4(Ov002TagTrackerNode *pNode);
extern int func_ov002_020536bc(int nTag);
extern void func_ov002_02053720(int nHandle, short nValue, short nKind);

void func_ov002_0205abe0(int nSlot, int nState, int nValue) {
    Ov002PanelSession *s = data_ov002_0207f620;
    int nHandle;

    func_ov002_0205abb8(nSlot, nState);
    func_ov002_02053578(s->aNodes[nSlot], nValue,
                        s->aNodes[nSlot]->nKind);
    func_ov002_020535a4(s->aNodes[nSlot]);

    if (nState != 0) {
        if (nState < 3) {
            return;
        }
        if (nState > 6) {
            return;
        }
    }
    nHandle = func_ov002_020536bc(2);
    func_ov002_02053720(nHandle, s->aNodes[nSlot]->nValue,
                        s->aNodes[nSlot]->nKind);
}
