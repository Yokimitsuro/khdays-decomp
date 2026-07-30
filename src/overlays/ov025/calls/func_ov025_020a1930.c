/* func_ov025_020a1930 -- Ov008_UpdateScrollGauge (208 B, 8 relocs).
 * Recomputes the menu list's scroll gauge after the entry list changes. Counts the objects in the
 * list at self+0x1cc, derives a per-step scale = 0x800 / (count * 2) (func_02020400), clamps it to
 * [0x20, 0x80] and stores it at self+0x4c. Then it toggles the visibility of the 14 gauge segments
 * (entry ids 0x30..0x3d) in the scene block: a segment is shown while its index (id - 0x30) is
 * within (scale - 0x20) / 8, otherwise hidden. A direct dependency of the menu page-rebuild tick
 * (func_ov008_0206ed7c) and of func_ov008_0206e410.
 * The scale is written to self+0x4c three times (once per clamp step, matching the ROM), and the
 * loop-invariant (scale-0x20)/8 keeps its final arithmetic shift inside the per-iteration compare. */
extern int  func_02020400(int a, int b);
extern int  NNS_FndGetNextListObject(void *list, int obj);
extern int  func_ov025_02084a8c(void);
extern int  func_ov025_0208843c(int ctx, int id);
extern void func_ov025_0208884c(int obj, int entry, int n);

void func_ov025_020a1930(int self)
{
    int count = 0;
    int q, block, base, id, entry, obj;

    for (obj = NNS_FndGetNextListObject((void *)(self + 0x1cc), 0); obj != 0;
         obj = NNS_FndGetNextListObject((void *)(self + 0x1cc), obj))
        count++;
    q = func_02020400(0x800, count << 1);
    *(int *)(self + 0x4c) = q;
    if (q <= 0x20)
        q = 0x20;
    *(int *)(self + 0x4c) = q;
    if (q >= 0x80)
        q = 0x80;
    *(int *)(self + 0x4c) = q;
    block = func_ov025_02084a8c();
    base = *(int *)(self + 0x4c) - 0x20;
    for (id = 0x30; id <= 0x3d; id++) {
        if (id - 0x30 <= base / 8) {
            entry = func_ov025_0208843c(block, id);
            func_ov025_0208884c(block, entry, 1);
        } else {
            entry = func_ov025_0208843c(block, id);
            func_ov025_0208884c(block, entry, 0);
        }
    }
}
