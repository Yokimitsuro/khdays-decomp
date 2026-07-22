/* func_ov025_0209ac58 -- handle the state-2 button. States 0 and 4 cancel (func_ov025_02084798
 * with -1); state 1 commits the pending edit (dialog, apply, clear the three 8-byte edit slots at
 * +0x140, reset the state); any other state just chirps. Always plays the confirm SFX.
 *
 * THE STRENGTH-REDUCTION "BLOCKED CLASS" IS NOT BLOCKED. This was parked 8 bytes over with the
 * note "the ROM keeps the loop counter live and scales it inline (add r0, base, i lsl#3;
 * str [r0,#0x140]) whereas mwcc spins up an induction variable; no spelling suppresses it", and
 * four sibling parks were filed the same way. The spelling that works is an ARRAY INDEX OVER AN
 * ELEMENT TYPE THE SIZE OF THE STRIDE, WITH THE FIELD OFFSET FOLDED INTO THE INDEX --
 * here `((Ov008Pair8 *)param_1)[i + 0x28].a = 0;`, an 8-byte element and 0x140 / 8 = 0x28.
 * `param_1[i * 2 + 0x50]` and `*(int *)((char *)param_1 + i * 8 + 0x140)` both reduce to a running
 * pointer; folding the offset into the index does not, because there is no expression left to
 * strength-reduce: the scale IS the element size and the constant IS an addressing-mode immediate.
 */
typedef struct { int a, b; } Ov008Pair8;

extern int func_ov025_02084a7c(void);
extern void func_ov025_02084798(int a, int b);
extern void func_ov025_0209b138(int a, int b);
extern void func_ov025_0209b7a4(int *obj, int a);
extern void func_02033b78(int a, int b);

void func_ov025_0209ac58(int *param_1) {
    func_ov025_02084a7c();
    if (param_1[0x8f] != 0) {
        return;
    }
    switch (param_1[1]) {
    case 0:
    case 4:
        func_ov025_02084798(0, -1);
        break;
    case 1:
        func_ov025_0209b138(1, 0);
        func_ov025_0209b7a4(param_1, 0);
        {
            int i;
            for (i = 0; i < 3; i++) {
                ((Ov008Pair8 *)param_1)[i + 0x28].a = 0;
            }
        }
        param_1[1] = 0;
        break;
    }
    func_02033b78(0, 3);
}
