/* func_ov008_02074a4c -- Ov008_SwitchMenuTab (196 B, 7 relocs).
 * Switches the active menu tab from p->curTab to idx. For both the outgoing tab (p->curTab)
 * and the incoming tab (idx) it maps the index to a cell tag (0->0xf0, 1->0xf1, 2->0xf2 for the
 * old tab; 0->0xf3, 1->0xf4, 2->0xf5 for the new tab; anything else keeps the base tag), looks
 * the cell up (func_ov008_02055808) and re-registers it (func_ov008_0205589c). It then retargets
 * the sub-object at p+0xc to p->arr138[idx] (func_02030094) and applies p->arr144[idx]
 * (func_ov008_020748c0), and finally records the new tab in p->curTab.
 *
 * The tag mapping is written so the middle case (==1) sits in an else block: mwcc otherwise
 * predicates it inline and comes out one instruction short per mapping -- the else form forces
 * the ROM's out-of-line branch (cmp/beq to a separate mov) while the last case (==2) predicates. */
typedef unsigned char  u8;

typedef struct Ov008TabState {
    int field0;
    int curTab;                 /* 0x04 */
    int field8;
    u8  sub_000c[0x138 - 0xc];  /* 0x0c: sub-object retargeted per tab */
    int arr138[3];              /* 0x138 */
    int arr144[3];              /* 0x144 */
} Ov008TabState;

extern void *func_ov008_02050c3c(void);
extern void *func_ov008_02055808(void *ctx, int tag);
extern void  func_ov008_0205589c(void *ctx, void *cell);
extern void  func_02030094(void *p, void *target, int update);
extern void  func_ov008_020748c0(Ov008TabState *p, void *value);

void func_ov008_02074a4c(Ov008TabState *p, int idx)
{
    void *ctx = func_ov008_02050c3c();
    int old = p->curTab;
    int tag;

    tag = 0xf0;
    if (old != 0) {
        if (old != 1) {
            if (old == 2) {
                tag = 0xf2;
            }
        } else {
            tag = 0xf1;
        }
    }
    func_ov008_0205589c(ctx, func_ov008_02055808(ctx, (unsigned short)tag));

    tag = 0xf3;
    if (idx != 0) {
        if (idx != 1) {
            if (idx == 2) {
                tag = 0xf5;
            }
        } else {
            tag = 0xf4;
        }
    }
    func_ov008_0205589c(ctx, func_ov008_02055808(ctx, (unsigned short)tag));

    func_02030094(&p->sub_000c, (void *)p->arr138[idx], 1);
    func_ov008_020748c0(p, (void *)p->arr144[idx]);
    p->curTab = idx;
}
