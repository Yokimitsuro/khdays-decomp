/* Advance a node's mini-animation: if its kind (id at +2) matches the page's "done" marker
 * (+0x209c) or is one of the terminal kinds {0x13,0x14,0x15,0x1b}, clear the node and report done
 * (1); otherwise dispatch to the per-kind handler func_020343cc.
 *
 * NON-MATCHING (equivalent). The dense jump table over [0x13,0x1b] reproduces. Residue (8 bytes):
 * the ROM materialises the return value 1 in r0 once, up front, so both the marker check
 * (predicated moveq/streq/ldmiaeq) and the terminal-case block are just str+return; mwcc 139 will
 * neither hoist the 1 nor predicate the marker check, so it re-loads `mov r0,#1` per block and
 * branches. Tried a shared fall-through block (merges the two, 8 bytes short) and a result
 * variable (still duplicated). A return-value-hoist / predication compiler difference. */
extern int func_ov008_02050cd4(void);
extern int func_020343cc(int *node);

int func_ov008_0205ca8c(int *param_1) {
    int page = func_ov008_02050cd4();
    unsigned short id = *(unsigned short *)(*param_1 + 2);
    if (id == *(int *)(page + 0x209c)) {
        *param_1 = 0;
        return 1;
    }
    switch (id) {
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x1b:
        *param_1 = 0;
        return 1;
    default:
        return func_020343cc(param_1);
    }
}
