/* NONMATCHING — return-branch-sense tie (32/32, byte-equivalent). The ROM branches
 * to `return 1` on nonzero (bne) leaving `return 0` as the fall-through; mwcc
 * canonicalizes `return f() != 0` the other way (beq to `return 0`). Two instructions
 * (the movs order + beq/bne) swap; every other byte matches. Tried == 0/return, !=/
 * return and the ?: form. Blob keeps the build byte-exact.
 *
 * Query func_02021980(param_1); pass presence to func_ov002_0206f6b4, return success. */
extern int func_02021980(void *arg);
extern int func_ov002_0206f6b4(int present);

int func_ov002_02074c7c(void *param_1) {
    int x = func_02021980(param_1);
    return func_ov002_0206f6b4(x != 0) != 0;
}
