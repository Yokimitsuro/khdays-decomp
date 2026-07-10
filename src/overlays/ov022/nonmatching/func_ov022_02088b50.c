/* NONMATCHING: 6-byte zero-fill coalescing/scheduler tie, 4 bytes short. The
 * original emits six individual `strb` (via a held sp pointer, interleaved with
 * the guard load) into the 6-byte marshalling buffer; from clean C mwcc coalesces
 * two of the adjacent zero stores into one halfword unless the buffer is written
 * through an explicit `char *`, which then costs an extra callee-saved register.
 * Neither form matches both the store count and the register allocation. Tried:
 * char[6]/char[7]/char[8], a 6-field byte struct, volatile, an explicit pointer,
 * and pointer-free indexed access. Semantics are exact. */
extern int func_ov022_020881f8(int obj);
extern void func_ov022_02088474(int obj);
extern int func_ov002_02072754(void);
extern void func_02077cec(void *buf, int a, void *entry);
extern int data_ov022_020b2e78;

struct Entry02088b50 { int a, b, c; };

void func_ov022_02088b50(int obj, int idx, int val) {
    char buf[6];
    struct Entry02088b50 entry;
    buf[0] = 0; buf[1] = 0; buf[2] = 0; buf[3] = 0; buf[4] = 0; buf[5] = 0;
    if (*(int *)((char *)&data_ov022_020b2e78 + 4) == 0) return;
    if (val > 100) val = 100;
    buf[idx] = (char)val;
    entry = *(struct Entry02088b50 *)func_ov022_020881f8(obj);
    entry.b += 0x800;
    func_ov022_02088474(obj);
    func_02077cec(buf, (unsigned short)func_ov002_02072754(), &entry);
}
