extern void VeneerTo_Obj_Destroy(int handle);
extern char data_ov027_02083ee0[];
/* Slot 2 of the scene hooks: destroy the scene's task if there is one (+4, -1 = none). */
void Ov027_DestroySceneTask(void) {
    int handle = *(int *)(data_ov027_02083ee0 + 4);
    if (handle != -1) {
        VeneerTo_Obj_Destroy(handle);
    }
}
