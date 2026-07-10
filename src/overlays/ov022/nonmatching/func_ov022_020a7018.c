/* NONMATCHING: single callee-saved register-coloring tie, byte-exact structure.
 * The original colors {r=r4, ok=r5, tail=r6}; mwcc puts tail in r5 and the second
 * zero-init in r6 instead. Seven forms tried (four declaration orders, int vs
 * char* tail, one-line init, a +0x2BB2 base). Semantics exact: when the state
 * byte at +0x7B4 is 3, arms the transition (020a35f4 mode 0xF, then clears the
 * state) if the sub-buffer's word[1] is within +/-0xC00 of obj[0x490], or the
 * byte at +0x2BB2 is 2. */
extern int func_ov022_020ad114(int obj);
extern int func_ov022_020ad0c0(int obj);
extern int func_ov022_020a35f4(int obj, int mode);

struct Vec3_020a7018 { int a, b, c; };

int func_ov022_020a7018(int obj) {
    int r = 0;
    int ok = 0;
    signed char *tail = (signed char *)(obj + 0x2bb0);
    if (*(unsigned char *)(obj + 0x7b4) != 3) return 0;
    if (func_ov022_020ad114(obj)) {
        struct Vec3_020a7018 buf = *(struct Vec3_020a7018 *)func_ov022_020ad0c0(obj);
        int target = *(int *)(obj + 0x490);
        int v = buf.b;
        if (v < target) {
            if (v > target - 0xc00) ok = 1;
        } else {
            ok = v < target + 0xc00;
        }
    }
    if (tail[2] == 2) ok = 1;
    if (ok) {
        r = func_ov022_020a35f4(obj, 0xf);
        *(unsigned char *)(obj + 0x7b4) = 0;
    }
    return r;
}
