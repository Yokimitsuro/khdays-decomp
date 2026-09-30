/* Apply one roster slot to the entity's display node and latch its value.
 *
 * Does nothing while the session's leading word at root context + 0x8bcc is -1. Otherwise it takes
 * the entity's display id, resolves it, and fetches the node. With a node in hand it applies the
 * slot and then, only the FIRST time, latches the value: bit 5 of the node's leading word is the
 * already-latched marker, so while it is clear the halfword at node+0x80 is set to the value biased
 * by 0x8000 and bit 5 of the halfword at node+4 is set.
 *
 * Both apply paths of Ov002_StepRosterSlotPhase call this.
 *
 * Codegen note. func_ov022_0208840c TAKES the slot index. Because that argument is already in r0 on
 * entry and nothing sets it up, r0 stays live across the session read, which is why the ROM saves
 * the three parameters in the order second, third, first and routes the pool loads through r1 and
 * r2 instead of r0. Declaring that callee with no argument costs ten bytes. The 0x8000 bias needs
 * no literal: mwcc derives it by shifting the 0x20 mask left by ten and reuses the same 0x20 for
 * the test and the set.
 *
 * Ghidra carries this as Ov002_ApplyRosterSlotToNode over Ov002RosterSlot.
 */

extern char *data_ov002_0207fa00;

extern int func_ov022_0208840c(int index);
extern int LoadArrayU8At0cc(int id);
extern unsigned int *ArrayEntryPtrD0(int id);
extern void func_ov022_02088218(int index, void *slot);

void Ov002_ApplyRosterSlotToNode(int index, void *slot, int value) {
    int id;
    unsigned int *node;

    if (*(int *)(data_ov002_0207fa00 + 0x8bcc) == -1) {
        return;
    }
    id = func_ov022_0208840c(index);
    if (LoadArrayU8At0cc(id & 0xffff) == 0) {
        return;
    }
    node = ArrayEntryPtrD0((unsigned short)((unsigned short)id));
    if (node == 0) {
        return;
    }
    func_ov022_02088218(index, slot);
    if ((*node & 0x20) == 0) {
        *(short *)((char *)node + 0x80) = (short)(value + 0x8000);
        *(unsigned short *)((char *)node + 4) |= 0x20;
    }
}
