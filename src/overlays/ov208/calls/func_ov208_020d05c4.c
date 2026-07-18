/*
 * func_ov208_020d05c4 -- x3 (ov208/209/268). Detach all sub-nodes, then hand off.
 * Notify the owner via 020c2b38(arg, *(self+0x3b0)); walk the 5-entry table at *(self+0x40c):
 * for each live handle (word at +8*i+4) release it through 0203c650(*(self+0x3c), handle) and
 * clear the slot. Finish by ticking 020c7c1c(self, arg).
 */
extern void func_ov107_020c2b38(int owner, int node);
extern void func_0203c650(int scene, int handle);
extern void func_ov107_020c7c1c(int self, int arg);

struct slot { int a; int handle; };

void func_ov208_020d05c4(int self, int arg) {
    int i, handle;

    func_ov107_020c2b38(arg, *(int *)(self + 0x3b0));
    for (i = 0; i < 5; i++) {
        handle = ((struct slot **)self)[0x40c / 4][i].handle;
        if (handle != 0) {
            func_0203c650(*(int *)(self + 0x3c), handle);
            ((struct slot **)self)[0x40c / 4][i].handle = 0;
        }
    }
    func_ov107_020c7c1c(self, arg);
}
