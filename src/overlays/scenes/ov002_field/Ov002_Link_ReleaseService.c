/* Releases the link service instance. */

extern void VeneerTo_Obj_Destroy();
extern int data_ov002_0207f024;

void Ov002_Link_ReleaseService(void) {
    int p = *(int *)&data_ov002_0207f024;
    if (p == -1) {
        return;
    }
    VeneerTo_Obj_Destroy(p);
    data_ov002_0207f024 = -1;
}
