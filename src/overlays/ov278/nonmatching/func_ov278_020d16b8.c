/* NONMATCHING: semantics correct, same-size (68B) scheduling/regalloc tie. The ROM
 * schedules the owner load between the bit0 extract and the ternary, then reuses
 * obj's freed register (r2) for the 4/7 value (`lsrs; ldr r1,[r2]; movne r2,#4;
 * moveq r2,#7; strb r2,[r1,#0x1c7]`). mwcc 3.0/139 materializes the ternary value
 * first (into r3, obj still live) then loads owner. Tried owner-local, dst-pointer,
 * and inverted ternary — all shuffle the schedule but never free r2 for the value.
 * Twin ov278_020d16b8 is byte-identical and ties the same way.
 *
 * c634 reaction handler: bail if the busy byte (self->obj->f4 + 0xad) is set.
 * Latch owner->+0x1c7 = 4 if obj->+0x52 bit 0 is set, else 7, then dispatch state
 * with a null callback. self->+0x20 (signed) = slot index. */
extern void func_0203c634(int self, int index, void *cb);
struct bit0 { unsigned char b:1; };
void func_ov278_020d16b8(int self) {
    int obj = *(int *)(self + 4);
    if (*(unsigned char *)(*(int *)(obj + 4) + 0xad) != 0) {
        return;
    }
    *(unsigned char *)(*(int *)obj + 0x1c7) = ((struct bit0 *)(obj + 0x52))->b ? 4 : 7;
    func_0203c634(self, *(signed char *)(self + 0x20), 0);
}
