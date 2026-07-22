/* Map a kind code to one of four groups; callers use the result both as a bit index
 * (`1 << group`) and as an argument to func_ov022_0209398c. Kinds 5-7 and 0xb are group 1,
 * 8 and 9 group 2, 10 group 3, and everything else group 0.
 *
 * Kinds 2, 3 and 4 have to be spelled out as their own case group ASSIGNING 0, even though 0
 * is already the initial value: that is what gives the original its extra block, a lone branch
 * to the exit that the jump table sends 2/3/4 to instead of pointing them at the default. An
 * empty `break` group is not enough -- mwcc folds it back into the default and the function
 * comes out four bytes short. */
int func_ov022_02093a1c(int kind) {
    int group = 0;
    switch (kind) {
    case 2:
    case 3:
    case 4:
        group = 0;
        break;
    case 5:
    case 6:
    case 7:
    case 0xb:
        group = 1;
        break;
    case 8:
    case 9:
        group = 2;
        break;
    case 10:
        group = 3;
        break;
    }
    return group;
}
