/* Interworking tail-call veneer (`ldr ip,[pc] ; bx ip`): forwards to Obj_Destroy. */
extern void *Obj_Destroy();

void *VeneerTo_Obj_Destroy(int *arg0) {
    return Obj_Destroy(arg0);
}
