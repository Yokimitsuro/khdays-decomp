/* Destroy the roster object Ov002_Roster_Create made (if any) and mark its handle free. */
extern void VeneerTo_Obj_Destroy(int handle);
extern int data_ov002_0207f00c;

void Ov002_Roster_Release(void) {
    int handle = *(int *)&data_ov002_0207f00c;
    if (handle != -1) {
        VeneerTo_Obj_Destroy(handle);
        *(int *)&data_ov002_0207f00c = -1;
    }
}
