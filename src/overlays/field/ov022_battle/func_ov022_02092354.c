/* Destroys an effect set: releases the shared array when it is the last one and the six service
 * instances. */

extern void ClearGlobalArrayInt(int arg0);
extern void VeneerTo_Obj_Destroy(int arg0);
extern int data_ov022_020b2eac;

void func_ov022_02092354(int *arg0) {
    int c = *(int *)&data_ov022_020b2eac - 1;
    int i;
    *(int *)&data_ov022_020b2eac = c;
    if (c == 0) ClearGlobalArrayInt(10);
    i = 0;
    do {
        if (*arg0 != 0) VeneerTo_Obj_Destroy(*arg0);
        i = i + 1;
        arg0 = arg0 + 1;
    } while (i < 6);
}
