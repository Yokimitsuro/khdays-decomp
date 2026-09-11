/* MsgDb dispatcher: route by database id (db) to the per-database record decoder.
 * db 0..0x12 share one generic decoder (func_02034e3c handles that whole range
 * itself, keyed on db). db 0x17 and 0x18 share a decoder that also needs the
 * raw db value as a fourth argument. Every other db in range 0..0x20 has its
 * own one-database decoder taking just (rec_out, index, keep). Any db above
 * 0x20 fails outright. Case-body order (0x15,0x16,0x13,0x19,0x1a,0x1b,0x1c,
 * 0x14,0x1d,0x1e,0x1f,0x20,0x17/0x18,0..0x12) is the ROM's own source order,
 * confirmed against the jump table's raw offsets, not value-sorted. */
extern int func_0203445c(int *rec_out, unsigned int index, int keep);
extern int func_02034660(int *rec_out, int value, int keep);
extern int func_02034730(int *rec_out, int index, int keep);
extern int func_020347ec(int *rec_out, int index, int keep);
extern int func_0203488c(int *rec_out, int index, int keep);
extern int func_02034918(int *rec_out, int index, int keep);
extern int func_0203498c(int *rec_out, unsigned int index, int keep);
extern int func_020349ec(int *rec_out, int index, int keep);
extern int func_02034ac0(int *rec_out, int index, int keep);
extern int func_02034b5c(int *rec_out, int index, int keep);
extern int func_02034c04(int *rec_out, int index, int keep);
extern int func_02034ca0(int *rec_out, int index, int keep);
extern int func_02034d40(int *rec_out, unsigned int index, int keep, int db);
extern int func_02034e3c(int *param_1, int param_2, unsigned int param_3, int param_4);

int func_020342e8(int *rec_out, int db, unsigned int index, int keep) {
    switch (db) {
    case 0x15:
        return func_0203445c(rec_out, index, keep);
    case 0x16:
        return func_02034660(rec_out, index, keep);
    case 0x13:
        return func_02034730(rec_out, index, keep);
    case 0x19:
        return func_020347ec(rec_out, index, keep);
    case 0x1a:
        return func_0203488c(rec_out, index, keep);
    case 0x1b:
        return func_02034918(rec_out, index, keep);
    case 0x1c:
        return func_0203498c(rec_out, index, keep);
    case 0x14:
        return func_020349ec(rec_out, index, keep);
    case 0x1d:
        return func_02034ac0(rec_out, index, keep);
    case 0x1e:
        return func_02034b5c(rec_out, index, keep);
    case 0x1f:
        return func_02034c04(rec_out, index, keep);
    case 0x20:
        return func_02034ca0(rec_out, index, keep);
    case 0x17:
    case 0x18:
        return func_02034d40(rec_out, index, keep, db);
    case 0x0: case 0x1: case 0x2: case 0x3: case 0x4: case 0x5: case 0x6: case 0x7:
    case 0x8: case 0x9: case 0xa: case 0xb: case 0xc: case 0xd: case 0xe: case 0xf:
    case 0x10: case 0x11: case 0x12:
        return func_02034e3c(rec_out, db, index, keep);
    default:
        return 0;
    }
}
