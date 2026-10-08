/* Ov026_CreateMissionCell -- create and place a mission cell object, ov008.
 * Instantiates a cell in slot `slot` from resource `res` (VeneerTo_SlotTable_AddEntry),
 * makes it visible (Slot_SetMode2Bit), commits it (Slot_ClearFlagBit1), sets frame 0 (Slot_SetVisible)
 * and applies the transform passed by value via Slot_SetPosition. Returns the new object.
 *
 * Parked as a "frame-layout tie": the ROM homes all four arguments with `push {r0,r1,r2,r3}`
 * and passes `&xform` INTO that block (`add r2,sp,#0x1c`), while a plain 4-argument function
 * has to copy the transform to a stack slot of its own first. The push of r0-r3 is not a frame
 * choice, it is the VARIADIC prologue -- declare the function `...` and the block exists for
 * free, so `&xform` is the block slot and the copy disappears. `push {r0,r1,r2,r3}` at the top
 * of a function is always that tell. */
extern int  VeneerTo_SlotTable_AddEntry(int *mgr, unsigned int res, int slot);
extern void Slot_SetMode2Bit(int mgr, int obj, int a);
extern void Slot_ClearFlagBit1(int mgr, int obj);
extern void Slot_SetVisible(int mgr, int obj, int a);
extern void Slot_SetPosition(int mgr, int obj, int *xform);

int Ov026_CreateMissionCell(int *mgr, unsigned int res, int slot, int xform, ...) {
    int obj = VeneerTo_SlotTable_AddEntry(mgr, res, slot);
    Slot_SetMode2Bit((int)mgr, obj, 1);
    Slot_ClearFlagBit1((int)mgr, obj);
    Slot_SetVisible((int)mgr, obj, 0);
    Slot_SetPosition((int)mgr, obj, &xform);
    return obj;
}
