/* func_ov031_020b3534 (x4 family: ov050/070/088) - NON-MATCHING.
 * Semantically correct state-transition dispatch (param_2 0x2e/0x2f/0x30). Multiple
 * intertwined codegen ties: (1) the `param_2==0x2f||param_2==0x30` guard won't emit the
 * original's fused `cmp;cmpne;beq` (mwcc gives `cmp;beq;cmp;bne;b`, +1 instr) via ||,
 * goto, or double-negation; (2) orig hoists `add r1,this,#0x2c` (partial this+0x2c2c addr)
 * before the dispatch; (3) mov r5/r4 + cmp operand order differ. Not a single-lever fix.
 * asm stub stays byte-exact via dsd. */
extern void func_ov031_020b39d4(int a, int b);
extern void func_ov022_020a4490(int a, int b, int c, int d);
extern void func_ov031_020b3a20(int a, int b);
extern void func_ov022_020a384c(int a, int b);

void func_ov031_020b3534(int this, int param_2, int param_3, int param_4) {
    if (param_2 == 0x2e) goto case2e;
    if (!(param_2 != 0x2f && param_2 != 0x30)) goto case2f30;
    goto end;
case2e:
    if (*(int *)(this + 0x6bc) != param_2)
        func_ov031_020b39d4(this, this + 0x2c2c);
    goto end;
case2f30:
    if (*(int *)(this + 0x6bc) != param_2) {
        if (param_2 == 0x2f) {
            *(int *)(this + 0x2c2c) = 0;
            *(int *)(this + 0x2c34) = 0x9000;
            func_ov022_020a4490(this, 0xcb, 2, this + 0x2000);
            func_ov031_020b3a20(this + 0x2d50, 0);
        } else {
            *(int *)(this + 0x2c2c) = 1;
            *(int *)(this + 0x2c34) = 0x12000;
            func_ov022_020a4490(this, 0xcb, 3, this + 0x2000);
            func_ov031_020b3a20(this + 0x2c38, 0x9000);
            func_ov031_020b3a20(this + 0x2d50, 0x9000);
        }
    }
end:
    func_ov022_020a384c(this, param_2);
}
