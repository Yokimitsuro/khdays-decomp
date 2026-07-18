/* Guard polarity inverted on purpose: `if (slot != -1) return 0;` lets mwcc predicate
 * the whole tail (moveq/strbeq/moveq); testing for the SUCCESS case gives the ROM's
 * real `bxne lr` early exit followed by an unconditional body. */
int func_ov124_020d0328(char *arg) {
    char *inner = **(char ***)(arg + 0x214);
    if (inner[0x1c7] == -1) {
        inner[0x1c7] = 6;
        return 1;
    }
    return 0;
}
