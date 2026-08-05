/*
 * func_ov002_0205249c - symmetric halfword row-fill (ARM, reloc-free).
 *
 * Writes `param_4` into a row of the halfword buffer at param_1[0x28], filling param_3/2
 * cells outward from the row centre in both directions: the left half descends from index
 * 0xf (0xf, 0xe, ...) and the right half ascends from 0x10 (0x10, 0x11, ...). Each row is
 * 32 halfwords, selected by param_2 (row << 5). No-op when param_3/2 <= 0.
 *
 * The buffer pointer param_1[0x28] is re-read before each store because a store may alias it.
 * `i` is declared before `half` so the loop counter claims the lower register (r4).
 */
void func_ov002_0205249c(int param_1, int param_2, int param_3, short param_4)
{
    int i;
    int half = param_3 / 2;
    short *buf;

    for (i = 0; i < half; i++) {
        buf = *(short **)(param_1 + 0x28);
        buf[param_2 * 32 + (0xf - i)] = param_4;
        buf = *(short **)(param_1 + 0x28);
        buf[param_2 * 32 + 0x10 + i] = param_4;
    }
}
