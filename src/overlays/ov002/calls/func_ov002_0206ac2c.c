/*
 * Fill in the script request block of the root context.
 *
 * The script VM opcode handler at 02074ef0 reads four operands and lands them here: an id, a
 * parameter word, a duration and a flag word. A negative id means the opcode carries nothing to
 * post, so the whole block is left alone. The countdown at +0x74 is the duration scaled by
 * 2867/4096, a hair over seven tenths, and never allowed to reach zero, so a request always
 * lasts at least one tick.
 *
 * The block sits at 0x8c94 inside Ov002RootContext; Ghidra carries the field names
 * (nRequestParam, nRequestDuration, wRequestFlags, bRequestId, nRequestCountdown). Writing the
 * far offsets against the context base rather than the block pointer is what keeps the original
 * addressing, since the two THUMB accesses past the immediate range index off the base.
 */

typedef unsigned short u16;
typedef short s16;

extern char *data_ov002_0207fa00;

void func_ov002_0206ac2c(int index, int value, u16 duration, u16 flags) {
    char *base = data_ov002_0207fa00;
    char *slot = base + 0x8c94;

    if (index >= 0) {
        *(char *)(slot + 0x1a) = (char)index;
        *(int *)(slot + 0xc) = value;
        *(u16 *)(slot + 0x10) = duration;
        *(u16 *)(slot + 0x18) = flags;
        *(s16 *)(base + (0x8c94 + 0x74)) =
            (s16)(*(s16 *)(base + (0x8c94 + 0x10)) * 0xb33 >> 12);
        if (*(s16 *)(base + (0x8c94 + 0x74)) == 0) {
            *(s16 *)(base + (0x8c94 + 0x74)) = 1;
        }
    }
}
