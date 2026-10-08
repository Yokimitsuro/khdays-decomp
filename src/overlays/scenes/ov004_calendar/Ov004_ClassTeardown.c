/* Ov004_ClassTeardown -- destroy the object the context (data_ov004_02051380) points at, ov004
 * (a tail call to Obj_Destroy through its veneer). */
extern void *VeneerTo_Obj_Destroy(void *ctx);
extern void *data_ov004_02051380;
void *Ov004_ClassTeardown(void) {
    return VeneerTo_Obj_Destroy(*(void **)data_ov004_02051380);
}
