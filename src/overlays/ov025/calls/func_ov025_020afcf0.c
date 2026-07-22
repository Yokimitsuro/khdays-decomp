/* func_ov025_020afcf0 -- is the ov025 transfer idle? True when bit 2 of the flags word at +0x28 is
 * clear AND the pending handle at +0x1f4 is null. */
extern int func_ov025_02084b14(void);

struct Ov025Flags { unsigned int lo : 2, bit2 : 1, rest : 29; };

int func_ov025_020afcf0(void) {
    int ctx = func_ov025_02084b14();
    return ((struct Ov025Flags *)(ctx + 0x28))->bit2 == 0 && *(int *)(ctx + 0x1f4) == 0;
}
