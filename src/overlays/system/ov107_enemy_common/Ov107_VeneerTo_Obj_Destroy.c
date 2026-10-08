/* Interworking tail-call veneer: reaches Obj_Destroy through the main-module veneer
 * VeneerTo_Obj_Destroy. */
extern int VeneerTo_Obj_Destroy();
int Ov107_VeneerTo_Obj_Destroy(int obj) {
    return VeneerTo_Obj_Destroy(obj);
}
