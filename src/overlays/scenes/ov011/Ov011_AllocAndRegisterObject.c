/* Allocates a sprite slot for a cell and hides it. */

extern int VeneerTo_SlotTable_AddEntry();
extern void Slot_SetMode2Bit();
extern void Slot_SetVisible();

int Ov011_AllocAndRegisterObject(int this_, int arg1) {
    int obj = VeneerTo_SlotTable_AddEntry(this_, arg1, 0);
    Slot_SetMode2Bit(this_, obj, 0);
    Slot_SetVisible(this_, obj, 0);
    return obj;
}
