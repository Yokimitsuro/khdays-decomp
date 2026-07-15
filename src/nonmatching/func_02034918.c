/* NONMATCHING: semantics correct, 64-bit-copy idiom + param regalloc. The ROM copies
 * elem[0..1] to rec+0x10 as a 64-bit value with an explicit `+0` add (`movs 0; movs 0;
 * adds lo; adcs hi`); mwcc 3.0/139 renders `*(long long*)dst = *(long long*)elem`
 * (and `+0`/`+0LL`) as an ldm/stm block copy and spills elem, and swaps index/elem
 * (r6/r7). No C form reproduces the ROM's add-with-zero pair.
 *
 * MsgDb decoder for db 0x1b: bounds-check index, alloc a 0x18 record (kind 0x1b),
 * store index and the two words of elem into rec+0x10/0x14. elem = entry[8] +
 * index*8 (entry at table + 0x1b*0x14). */
extern int func_020342b4(int db);
extern int func_02034428(int *rec_out, int size, int kind, int keep);
extern int data_0204c238;
int func_02034918(int *rec_out, int index, int keep) {
    int *elem;
    int v, rec;
    if (func_020342b4(0x1b) == 0 || (keep >= 0 && *rec_out != 0)) {
        return 0;
    }
    if (index >= 0 && index < *(unsigned short *)(data_0204c238 + 0x228)) {
        elem = (int *)(*(int *)(data_0204c238 + 0x224) + index * 8);
        if (func_02034428(rec_out, 0x18, 0x1b, keep) == 0 || *rec_out == 0) {
            return 0;
        }
        *(int *)(*rec_out + 0xc) = index;
        v = elem[1];
        rec = *rec_out;
        *(int *)(rec + 0x10) = elem[0];
        *(int *)(rec + 0x14) = v;
        return 1;
    }
    return 0;
}
