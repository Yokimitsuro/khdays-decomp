/* Scene entry gate: when a validation hook is installed at root + 0x8b94, run it
 * and hand back no step if it refuses. Otherwise arm mode 1 and let
 * func_ov002_020693e0 have the final say, returning the step at
 * func_ov002_02068090. */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov002_0206e718(int mode);
extern int func_ov002_020693e0(void);
extern void func_ov002_02068090(void);

void *func_ov002_02068058(void) {
    int (*validate)(void) =
        *(int (**)(void))((char *)NNSi_FndGetCurrentRootHeap() + 0x8b94);

    if (validate != 0 && validate() == 0) {
        return 0;
    }

    func_ov002_0206e718(1);
    if (func_ov002_020693e0() == 0) {
        return 0;
    }
    return (void *)&func_ov002_02068090;
}
