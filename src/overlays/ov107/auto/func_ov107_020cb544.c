/* func_ov107_020cb544 -- clear the caller's bits in the task's 16-bit flags field at +0xc.
 * The field is a `unsigned lo : 16` BITFIELD: that is what produces the ROM's
 * `lsl #0x10 ; lsr #0x10` read-modify-write around a 32-bit load, instead of a plain `ldrh`. */
struct Ov107Flags { unsigned int lo : 16, hi : 16; };

void func_ov107_020cb544(int obj, unsigned int mask) {
    ((struct Ov107Flags *)(obj + 0xc))->lo &= ~mask;
}
