/* func_ov107_020cb578 -- reset the task: clear its two payload words and its 16-bit flags field,
 * set the 3-bit state field (bits 16..18) to 7, and re-arm it.
 * The word at +0xc is modelled as `unsigned lo:16, mid:3, rest:13`; the ROM's
 * `and ~0xffff ; bic #0x70000 ; orr #0x70000` triple is exactly two bitfield stores. */
extern void func_ov107_020cb51c(int obj, int a);

struct Ov107Flags2 { unsigned int lo : 16, mid : 3, rest : 13; };

void func_ov107_020cb578(int obj) {
    *(int *)obj = 0;
    *(int *)(obj + 4) = 0;
    ((struct Ov107Flags2 *)(obj + 0xc))->lo = 0;
    ((struct Ov107Flags2 *)(obj + 0xc))->mid = 7;
    func_ov107_020cb51c(obj, 1);
}
