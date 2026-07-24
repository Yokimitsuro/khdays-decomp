/* MsgDb decoder for db 0x1b: bounds-check `index`, allocate a 0x18-byte record of kind 0x1b,
 * then store the index at rec+0xc and the two words of the table element at rec+0x10/0x14.
 * elem = entry[8] + index*8, where entry is the 0x1b'th 0x14-byte row of the db table.
 *
 * The old park note claimed "the ROM copies elem[0..1] as a 64-bit value with an explicit `+0`
 * add (movs 0; movs 0; adds lo; adcs hi) ... no C form reproduces the ROM's add-with-zero pair".
 * There is one, and it needs three separate things, each of which alone leaves a residue:
 *   - the zero must survive constant folding, which takes TWO statements: `long long acc = 0;`
 *     and then a separate `acc = acc + ...`. Written as one expression (`0LL + e`, `e + 0`,
 *     or a `z` initialised in the same declaration) mwcc folds the add away and emits a plain
 *     64-bit copy, 8 bytes short;
 *   - the element must be assembled half by half -- `(unsigned int)elem[0]` for the low word and
 *     `((unsigned long long)(unsigned int)elem[1] << 32)` for the high one. Reading it as one
 *     `*(long long *)elem` makes mwcc materialise a single zero register and reuse it for both
 *     the adds and the adcs, so only one `movs #0` comes out;
 *   - BOTH halves must be unsigned. With `elem[0]` signed, mwcc sign-extends it into the high
 *     word (`asrs r0, r1, #0x1f`) and the add gains an instruction.
 * The destination is two 32-bit stores, not a 64-bit one: `*(long long *)(rec + 0x10) = acc`
 * makes mwcc build a second base register for the high word (+4 bytes). */
extern int func_020342b4(int db);
extern int func_02034428(int *rec_out, int size, int kind, int keep);
extern int data_0204c238;

int func_02034918(int *rec_out, int index, int keep) {
    int *elem;
    int rec;
    if (func_020342b4(0x1b) == 0 || (keep >= 0 && *rec_out != 0)) {
        return 0;
    }
    if (index >= 0 && index < *(unsigned short *)(data_0204c238 + 0x228)) {
        elem = (int *)(*(int *)(data_0204c238 + 0x224) + index * 8);
        if (func_02034428(rec_out, 0x18, 0x1b, keep) == 0 || *rec_out == 0) {
            return 0;
        }
        *(int *)(*rec_out + 0xc) = index;
        {
            long long acc = 0;
            acc = acc + (unsigned int)elem[0]
                      + ((unsigned long long)(unsigned int)elem[1] << 32);
            rec = *rec_out;
            *(int *)(rec + 0x10) = (int)acc;
            *(int *)(rec + 0x14) = (int)((unsigned long long)acc >> 32);
        }
        return 1;
    }
    return 0;
}
