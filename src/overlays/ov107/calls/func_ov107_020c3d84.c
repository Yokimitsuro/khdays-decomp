extern void func_0203c7e8(void *obj);
extern void *func_01fffd70(void *list);
extern void *func_01fffd8c(void *list);
extern void WM_EndKeySharing_0x020c3190(void *obj);
extern void NNSi_FndDestroyDoubleList(void *list);
extern void func_ov107_020c0d74(void *self);

/* Derived destructor: release the sub-object at self+0x9c, then empty the list
 * at self+0x144 (destroying each entry's payload), destroy the list itself, and
 * hand off to func_ov107_020c0d74 for the base teardown.
 *
 * 0x144 is materialised as `movs #0x51; lsls #2` -- that is just how THUMB
 * builds the constant, not a scaled index. */
void func_ov107_020c3d84(char *self) {
    void **entry;

    if (*(void **)(self + 0x9c) != 0) {
        func_0203c7e8(*(void **)(self + 0x9c));
    }
    entry = (void **)func_01fffd70(self + 0x144);
    if (entry != 0) {
        do {
            WM_EndKeySharing_0x020c3190(*entry);
            entry = (void **)func_01fffd8c(self + 0x144);
        } while (entry != 0);
    }
    NNSi_FndDestroyDoubleList(self + 0x144);
    func_ov107_020c0d74(self);
}
