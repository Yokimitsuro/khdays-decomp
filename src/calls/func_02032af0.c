/*
 * Sound_UpdateSpatial - recompute a sound slot's volume and pan from its 3D
 * position relative to the listener, then push both to its audio channel.
 *
 * With base = *data_0204c234 (the listener/world state): unless the slot's
 * "no-spatialise" flag (flags & 4, at snd+0x14) is set, take delta = position
 * (snd+8) - listener (base+0xb44cc) and dist = |delta|. Volume (unless flag 2
 * forces 0x7f): full (base+0xb46f4) when dist <= near (base+0xb46ec), 0 beyond
 * far (base+0xb46f0), else linearly attenuated by FX_Inv over the near..far band.
 * Pan comes from the dot product of delta with the listener's right vector
 * (base+0xb44d8) scaled by FX_Inv(dot, dist). Track mask 0xffff.
 *
 * The `(flags & 4)` test is written non-inverted (the zero-volume case first) so
 * mwcc predicates it as `movne` instead of a separate tail block.
 */

extern unsigned char *data_0204c234;
extern void VEC_Subtract(int *a, int *b, int *out);
extern int VEC_Mag(int *v);
extern int VEC_DotProduct(int *a, int *b);
extern int FX_Inv(int num, int den);
extern void func_0201a1a0(int *ch, int mask, int val);
extern void func_0201a170(int *ch, int mask, int val);

void func_02032af0(int param_1)
{
    int base = (int)data_0204c234;
    int delta[3];
    int vol;

    if ((*(unsigned short *)(param_1 + 0x14) & 4) != 0) {
        vol = 0;
    } else {
        int dist;
        VEC_Subtract((int *)(param_1 + 8), (int *)(base + 0xb44cc), delta);
        dist = VEC_Mag(delta);
        if ((*(unsigned short *)(param_1 + 0x14) & 2) == 0) {
            int near = *(int *)(base + 0xb46ec);
            if (dist <= near) {
                vol = *(short *)(base + 0xb46f4);
            } else if (dist < *(int *)(base + 0xb46f0)) {
                int t = FX_Inv(dist - near, *(int *)(base + 0xb46f0) - near);
                vol = (0x1000 - t) * (int)*(short *)(base + 0xb46f4) >> 0xc;
            } else {
                vol = 0;
            }
        } else {
            vol = 0x7f;
        }
        {
            int dot = VEC_DotProduct(delta, (int *)(base + 0xb44d8));
            int p = FX_Inv(dot, dist);
            func_0201a1a0((int *)(param_1 + 0x1c), 0xffff, (p << 7) >> 0xc);
        }
    }
    func_0201a170((int *)(param_1 + 0x1c), 0xffff, vol);
}
