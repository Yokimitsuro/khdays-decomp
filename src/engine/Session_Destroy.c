/* Tears the wireless session down: releases its two service instances and clears the session
 * pointer. */

extern int *NNSi_FndGetCurrentRootHeap(void);
extern void VeneerTo_Obj_Destroy(int arg);
extern int data_0204c228;

void Session_Destroy(void) {
    int *p = NNSi_FndGetCurrentRootHeap();
    VeneerTo_Obj_Destroy(p[9]);
    VeneerTo_Obj_Destroy(p[10]);
    data_0204c228 = 0;
}
