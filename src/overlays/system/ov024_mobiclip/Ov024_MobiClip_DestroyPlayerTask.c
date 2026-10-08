/* Ov024_MobiClip_DestroyPlayerTask -- slot 2 of the same table: destroy the movie player's task
 * if there is one (data_ov024_02093900, -1 = none). */
extern void VeneerTo_Obj_Destroy(void *handle);
extern int data_ov024_02093900;
void Ov024_MobiClip_DestroyPlayerTask(void) {
    if (data_ov024_02093900 != -1) {
        VeneerTo_Obj_Destroy((void *)data_ov024_02093900);
    }
}
