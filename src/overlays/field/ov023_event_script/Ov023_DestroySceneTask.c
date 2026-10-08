/* Ov023_DestroySceneTask -- slot 2 of the event scene's hook table: destroy the scene's task if
 * there is one (data_ov023_0208a000, -1 = none). */
extern void VeneerTo_Obj_Destroy(void *handle);
extern int data_ov023_0208a000;
void Ov023_DestroySceneTask(void) {
    if (data_ov023_0208a000 != -1) {
        VeneerTo_Obj_Destroy((void *)data_ov023_0208a000);
    }
}
