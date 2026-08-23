/*
 * Ov002_RewindWidget - put a widget back to the start of its animation.
 *
 * Both of its animated slots are re-bound to the sub-node and driven back to
 * zero, then the widget is refreshed - held on the first frame when the caller
 * asks for it, free-running otherwise.
 *
 * ARM.
 */

extern void func_0202accc(void *pWidget, int nSlot, void *pNode, int nFlags);
extern void func_01fff774(void *pWidget, int nSlot, int nValue);
extern void func_0202af1c(void *pWidget);
extern void func_0202af2c(void *pWidget);

void func_ov002_02061830(void *pWidget, int bHold)
{
    func_0202accc(pWidget, 0, (char *)pWidget + 0xe0, 0);
    func_0202accc(pWidget, 2, (char *)pWidget + 0xe0, 0);
    func_01fff774(pWidget, 0, 0);
    func_01fff774(pWidget, 2, 0);
    if (bHold != 0) {
        func_0202af2c(pWidget);
    } else {
        func_0202af1c(pWidget);
    }
}
