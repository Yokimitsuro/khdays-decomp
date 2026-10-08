/* Releases the service class instance, if any, and forgets its id. */

extern void VeneerTo_Obj_Destroy(int arg);

extern int data_02042978;

void ReleaseServiceInstance(void) {
    if (data_02042978 == -1) return;
    VeneerTo_Obj_Destroy(data_02042978);
    data_02042978 = -1;
}
