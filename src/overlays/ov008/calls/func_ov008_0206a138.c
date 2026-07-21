/* Unless story flag 0x200d is set, arm four "unseen" markers in the ov008 UI state block; and
 * whenever the shared game-state bit at +0x9b0 is set, arm a fifth. */
typedef unsigned char u8;
extern int func_02023588(int flagId);
extern u8 data_ov008_02090598[];
extern u8 *data_0204be18;

void func_ov008_0206a138(void) {
    if (func_02023588(0x200d) == 0) {
        data_ov008_02090598[0x132] = 1;
        data_ov008_02090598[0x146] = 1;
        data_ov008_02090598[0x15a] = 1;
        data_ov008_02090598[0x16e] = 1;
    }
    if (data_0204be18[0x9b0] != 0) {
        data_ov008_02090598[0x1e6] = 1;
    }
}
