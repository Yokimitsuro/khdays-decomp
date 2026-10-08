/* Slot 2 of the scene hooks: destroy the camp menu's task, if there is one. */

extern void VeneerTo_Obj_Destroy();
extern int data_ov025_020b49c0;

void Ov025_DestroyMenuTask(void) {
    int v = data_ov025_020b49c0;
    if (v == -1) {
        return;
    }
    VeneerTo_Obj_Destroy(v);
}
