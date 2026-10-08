extern void VeneerTo_Obj_Destroy(int handle);
extern void Ov002_World_ClearPending(void);
extern char *data_ov002_0207fa00;
/* Destroy the pause menu object at root +0x8d10 (Ov002_CreateOverlayObjectOutsidePhases makes it
 * from the pause menu class), if there is one, and clear what the world has pending. */
void Ov002_DestroyPauseMenu(void) {
    int handle = *(int *)((int)data_ov002_0207fa00 + 0x8d10);
    if (handle != -1) {
        VeneerTo_Obj_Destroy(handle);
        Ov002_World_ClearPending();
    }
}
