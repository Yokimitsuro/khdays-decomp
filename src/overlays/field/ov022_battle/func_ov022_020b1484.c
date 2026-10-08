/* Releases the battle helper instance when it exists. */

extern void VeneerTo_Obj_Destroy(int arg0);
extern int data_ov022_020b2eb8;

void func_ov022_020b1484(void) {
    if (((int *)&data_ov022_020b2eb8)[0] != 0 && ((int *)&data_ov022_020b2eb8)[1] != 0) {
        VeneerTo_Obj_Destroy(((int *)&data_ov022_020b2eb8)[1]);
        ((int *)&data_ov022_020b2eb8)[1] = 0;
    }
}
