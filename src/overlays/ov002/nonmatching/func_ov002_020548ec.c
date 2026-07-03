/*
 * func_ov002_020548ec — fill a rectangular tilemap region's palette nibble.
 *
 * Over a height x width region (height=(short)s[0xc], width=(short)s[0xa]),
 * for each row i set the high nibble (bits 12-15 = palette) of every tile
 * halfword to (value & 0xf), preserving the low 12 bits (mask 0xfff). The row
 * origin in the tilemap is base + 6 + s[6] + (mapwidth*(s[8]+i))/8, where
 * base = *(unsigned short**)(s[0x18]+8) and mapwidth = *base. First parameter
 * (r0) is unused (repurposed as the outer counter). insert = (value&0xf)<<12.
 *
 * NON-MATCHING: semantics exact and instruction count matches (152B), but the
 * nested-loop body has ~32 scheduling/register-coloring differences the
 * compiler won't reproduce: the original hoists value<<0x1c into a scratch reg
 * (freeing r2 for the mask, kept live across the inner loop) and schedules the
 * width (s[0xa]) load early into a callee-saved reg, keeping base in r8 / s[6]
 * in r7; mwcc spends r2 on value<<0x1c and reloads the mask/width later, using
 * fewer callee-saved registers. No decl/ordering form flips the allocation.
 * Same class as the documented scheduler/coloring ties. Affects the 3 siblings.
 */
void func_ov002_020548ec(int a0, int s, int value)
{
    unsigned int ins = value << 0x1c;
    int i = 0;
    if (0 < *(short *)(s + 0xc)) {
        do {
            unsigned short *base = *(unsigned short **)(*(int *)(s + 0x18) + 8);
            int prod = (unsigned int)*base * ((unsigned int)*(unsigned short *)(s + 8) + i);
            unsigned short *p = base + (unsigned int)*(unsigned short *)(s + 6) + prod / 8 + 6;
            int j = 0;
            if (0 < *(short *)(s + 10)) {
                do {
                    j = j + 1;
                    *p = *p & 0xfff | ins >> 0x10;
                    p = p + 1;
                } while (j < *(short *)(s + 10));
            }
            i = i + 1;
        } while (i < *(short *)(s + 0xc));
    }
}
