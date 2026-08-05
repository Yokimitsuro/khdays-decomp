/*
 * func_ov002_0205b728 - classify a cell into one of three result codes (ARM, reloc-free).
 *
 * Inputs are two coordinates (param_1, param_2) and a mode (param_3):
 *   - When both coordinates are inside the 0..9 core region, the cell is either 0xc (mode 2 or 3)
 *     or 0xb (any other mode).
 *   - Otherwise (a coordinate is >= 0xa, i.e. in the border band), the cell is 0xd when the mode
 *     matches the overflowing axis (mode 2 with param_1 in the band, or mode 3 with param_2 in the
 *     band), and 0xc in every other border case.
 *
 * The border case is written as the if-body (inverted condition) so mwcc emits the combined
 * `cmp; cmplt; blt` test that jumps to the core case placed out of line at the end; the two 0xd
 * conditions share one `return 0xd` via a single `||`, and the core case uses the
 * conditional-compare + conditional-move idiom for its (mode==2||mode==3) ? 0xc : 0xb result.
 */
int func_ov002_0205b728(int param_1, int param_2, int param_3)
{
    if (param_1 >= 0xa || param_2 >= 0xa) {
        if ((param_3 == 2 && param_1 >= 0xa) || (param_3 == 3 && param_2 >= 0xa))
            return 0xd;
        return 0xc;
    }
    return (param_3 == 2 || param_3 == 3) ? 0xc : 0xb;
}
