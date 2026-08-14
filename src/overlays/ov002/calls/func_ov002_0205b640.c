/* Show or hide one value row of the panel, as a pair of tag-tracker nodes.
 *
 * While the session state is non-zero both nodes are simply disarmed and
 * nothing else happens. Otherwise the label node is armed, and the value node
 * is filled with nValue under kind 0x11 and armed only when the caller says the
 * row is on screen -- bVisible is both the condition and the armed state it
 * ends up in. bRefresh adds the node reset to each node the call touches.
 *
 * nValue reaches the setter sign-extended from 16 bits, which is why the setter
 * declares it short: the truncation belongs to the callee prototype, not to a
 * cast here. All three list classes of the panel repaint converge on this call.
 */
typedef unsigned char u8;

typedef struct {
    u8 pad0000[0x10];
    int nState;             /* +0x10 */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern void func_ov002_020536dc(int nHandle, int bArmed);
extern void func_ov002_02053700(int nHandle);
extern void func_ov002_02053720(int nHandle, short nValue, int nKind);

void func_ov002_0205b640(int nTop, int nMain, int nValue, int bRefresh,
                         int bVisible) {
    Ov002PanelSession *s = data_ov002_0207f620;

    if (s->nState != 0) {
        func_ov002_020536dc(nTop, 0);
        func_ov002_020536dc(nMain, 0);
        return;
    }
    if (bRefresh != 0) {
        func_ov002_02053700(nTop);
    }
    func_ov002_020536dc(nTop, 1);
    if (bVisible != 0) {
        func_ov002_02053720(nMain, nValue, 0x11);
        if (bRefresh != 0) {
            func_ov002_02053700(nMain);
        }
    }
    func_ov002_020536dc(nMain, bVisible);
}
