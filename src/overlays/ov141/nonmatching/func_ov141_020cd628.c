/* NONMATCHING: equivalent C, div-by-constant internal-lowering tie (count=5,
 * 196B). Byte-exact EXCEPT mwcc's own codegen for the signed `(x*30)/5` (magic
 * 0x66666667 = ceil(2^34/10), so /5 of the *30): value/magic land in swapped
 * registers (orig value->r1/magic->r2, mwcc value->r2/magic->r1) and the sign
 * extract `m>>31` is scheduled before the smull (orig) vs after (mwcc). Only
 * the div sequence differs (14 bytes); the magic + size are correct and no C
 * form changes the internal order (inline, m-bound, v-bound, operand order).
 * (`x*6` is WRONG -- mwcc folds it to a plain mul, 176B; orig keeps *30 then
 * magic /5.) Semantics: like AimSubtractVecSetAngle but VEC_Subtract b-arg is
 * holder->0x3c, zeroes local[1], stores angle to holder->0xc, holder->0x10 =
 * (*this)->0x2c*30/5, advance with func_ov141_020cd6ec callback. */
extern int func_ov107_020cab14(int node, int flag);
extern int func_0203c634();
extern int VEC_Subtract();
extern int func_01ff8d18();
extern int func_020050b4();
extern int func_ov141_020cd6ec();

void func_ov141_020cd628(int this_) {
    int holder = *(int *)(this_ + 4);
    int local[3];
    int r;

    r = func_ov107_020cab14(*(int *)holder, 0);
    *(int *)(holder + 4) = r;
    if (r == 0) {
        *(signed char *)(*(int *)holder + 0x1c7) = 2;
        func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
        return;
    }

    VEC_Subtract(r + 0x190, *(int *)(holder + 0x3c), local);
    local[1] = 0;
    func_01ff8d18(local, local);
    *(int *)(holder + 0xc) = func_020050b4(local[0], local[2]);
    *(int *)(holder + 0x10) = *(int *)(*(int *)this_ + 0x2c) * 0x1e / 5;

    func_0203c634(this_, *(signed char *)(this_ + 0x20), func_ov141_020cd6ec);
}
