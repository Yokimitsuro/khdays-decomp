/* func_ov008_0204dd24 -- main-menu top state, ov008.
 * NONMATCHING: bitfield-codegen tie. The retail build accesses heap fields 0x1e/0x48/0x12b
 * as C bitfields (unsigned f:N), which mwcc lowers to lsl/lsr shift-extraction; our plain
 * &/>>/<< forms lower to shorter tst/and (-7 instr). Reproducing it needs the exact struct
 * bitfield layout. Logic is exact; kept for the PC port.
 *
 * Each frame updates the cursor (func_ov008_0204da6c) and input/state (func_ov008_0204d564).
 * While a sub-scene is active (func_ov008_0204ed3c) it stays until all 3 slots report done;
 * while idle it stays unless a confirmed selection (heap[0x2c]) fires. On commit it queues the
 * two transition events (func_020235d0 0x451/0x44e) into heap[0x12b] and advances to
 * func_ov008_0204de40. */
extern void func_ov008_0204da6c(void);
extern void func_ov008_0204d564(void);
extern int  func_ov008_0204ed3c(void);
extern void *func_020315c0(int slot);
extern unsigned char *func_ov008_0204ecd8(int slot);
extern int  func_ov008_0207bb14(void);
extern int  func_020235d0(int event, int arg);
extern char *data_ov008_02090f00;
extern void func_ov008_0204de40(void);

void *func_ov008_0204dd24(void) {
    func_ov008_0204da6c();
    func_ov008_0204d564();
    if (func_ov008_0204ed3c() != 0) {
        int slot;
        for (slot = 1; slot < 4; slot++) {
            if (func_020315c0(slot) != 0 && (func_ov008_0204ecd8(slot)[2] & 1) == 0) {
                return 0;
            }
        }
    } else {
        char *heap = data_ov008_02090f00;
        if ((*(unsigned char *)(heap + 0x1e) >> 4) < 1) {
            if (*(unsigned short *)(heap + 0x2c) != 0) {
                *(unsigned char *)(heap + 0x48) =
                    (*(unsigned char *)(heap + 0x48) & ~1) | (func_ov008_0207bb14() & 1);
            }
            return 0;
        }
    }
    *(unsigned char *)(data_ov008_02090f00 + 0x12b) =
        (*(unsigned char *)(data_ov008_02090f00 + 0x12b) & ~1) | (func_020235d0(0x451, 1) & 1);
    *(unsigned char *)(data_ov008_02090f00 + 0x12b) =
        (*(unsigned char *)(data_ov008_02090f00 + 0x12b) & ~0xe) | ((func_020235d0(0x44e, 3) & 7) << 1);
    return (void *)func_ov008_0204de40;
}
