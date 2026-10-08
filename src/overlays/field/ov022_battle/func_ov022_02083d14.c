/* Releases the context's service instance. */

extern void VeneerTo_Obj_Destroy(int arg0);
extern int data_ov022_020b2e60;

void func_ov022_02083d14(void) {
    VeneerTo_Obj_Destroy(*(int *)((char *)&data_ov022_020b2e60 + 4));
}
