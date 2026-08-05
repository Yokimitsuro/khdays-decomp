/*
 * func_ov002_02061908 - extract a decimal digit of param_2 (ARM, reloc-free).
 *
 * Divides param_2 by ten param_1 times, i.e. shifts param_2 right by param_1 decimal places,
 * then returns that value's last decimal digit (v % 10). Returns 0 when both inputs are 0, and
 * -1 when the shifted value is <= 0 (no digit at that place). Used to render a multi-digit
 * counter one digit at a time (param_1 selects the place). The divisions compile to the standard
 * signed divide-by-10 (smull by 0x66666667 + shift).
 */
int func_ov002_02061908(int param_1, int param_2)
{
    int v = param_2;
    int i;
    if (param_1 == 0 && param_2 == 0) return 0;
    for (i = 0; i < param_1; i++) {
        v = v / 10;
    }
    if (v <= 0) return -1;
    return v % 10;
}
