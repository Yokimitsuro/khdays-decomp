/* Releases the object service instance. */

extern void VeneerTo_Obj_Destroy();
extern int data_ov002_0207fa18;

void Ov002_ReleaseObjectService(void) {
    int p = *(int *)((char *)&data_ov002_0207fa18 + 4);
    if (p != 0) {
        VeneerTo_Obj_Destroy(p);
        *(int *)((char *)&data_ov002_0207fa18 + 4) = 0;
    }
}
