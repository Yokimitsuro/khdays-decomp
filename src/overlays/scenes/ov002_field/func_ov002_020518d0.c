/* Releases the service instance held at data_ov002_0207f600 + 4. */

extern int data_ov002_0207f600;
extern int VeneerTo_Obj_Destroy();

int func_ov002_020518d0(void) {
    return VeneerTo_Obj_Destroy(*(int *)((char *)&data_ov002_0207f600 + 4));
}
