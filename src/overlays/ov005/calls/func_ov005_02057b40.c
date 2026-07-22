/* func_ov005_02057b40 -- scale `a` by the percentage func_ov005_02057acc reports for `b`.
 * The `/ 100` is the signed magic-reciprocal divide (smull by 0x51eb851f, asr #5 plus the sign
 * fixup), which is what `/ 100` compiles to -- it is not a shift. */
extern int func_ov005_02057acc(int a);

int func_ov005_02057b40(int a, int b) {
    return a * func_ov005_02057acc(b) / 100;
}
