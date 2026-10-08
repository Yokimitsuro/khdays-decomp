extern void VeneerTo_Obj_Destroy(int handle);
extern char *data_ov026_02091360;
/* Slot 2 of the scene hooks: destroy the shop's service task (state +8, made by
 * Ov026_CreateService) when the shop's state exists. */
void Ov026_DestroyService(void) {
    int ctx = (int)data_ov026_02091360;
    if (ctx == 0) {
        return;
    }
    VeneerTo_Obj_Destroy(*(int *)(ctx + 8));
}
