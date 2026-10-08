/* Interworking tail-call veneer (`ldr ip,[pc] ; bx ip`): forwards to SlotTable_AddEntry. */
extern void *SlotTable_AddEntry();

void *VeneerTo_SlotTable_AddEntry(void *arg0, int arg1, int arg2) {
    return SlotTable_AddEntry(arg0, arg1, arg2);
}
