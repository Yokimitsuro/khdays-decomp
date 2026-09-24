/* Rejoin tick of the ov237 actor: the +0x3c aim point resets to data_ov237_020d1bf4; within 2.0 of its
 * +0x4c4 point (or on a +0x17a bit 0 contact) the pair merges back. Linked, the partner (+0x4a4) takes
 * the actor's health (clamped to its maximum), drops +0x4b0, clears bit 0 and sets bits 1, 2, 6 and 7
 * of its +0x60 high byte, sets bit 0 of +0x1ae and both rigs clear flag 1, and the actor moves onto the
 * partner's pose; alone, the health is saved in +0x4a0 and the same flags change on the actor itself.
 * Then +0x60 / +0x64 are set, effect 0x12 plays, the rig's flag 0 clears, the merge sound (0x12d
 * variant 0x11) plays and the brain waits on 020d09cc. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;
typedef struct { u8 b0 : 1; } Bit0;

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_ov107_020c5c54(int owner, const Vec3 *pos);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5af8(int actor, int bank, int variant, int at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov237_020d09cc(void);
extern const Vec3 data_ov237_020d1bf4;

void func_ov237_020d06e0(int *node)
{
    int *state = (int *)node[1];
    Vec3 from;
    Vec3 to;
    Vec3 d;
    int dist;

    from = *(Vec3 *)state[0xe];
    to = *(Vec3 *)(*state + 0x4c4);
    VEC_Subtract(&to, &from, &d);
    dist = func_01ff8d18(&d, &d);
    *(Vec3 *)(state + 0xf) = data_ov237_020d1bf4;
    if (!(dist >= 0x2000 && !((Bit0 *)(*state + 0x17a))->b0)) {
        if (*(int *)(*state + 0x4ac) != 0) {
            int hp = *(short *)(*state + 0x21a);
            char *partner = *(char **)(*state + 0x4a4);

            *(short *)(partner + 0x21a) = hp < 0 ? 0 : (hp > *(short *)(partner + 0x218) ? *(short *)(partner + 0x218) : hp);
            *(int *)(*(int *)(*state + 0x4a4) + 0x4b0) = 0;
            {
                u16 hw = *(u16 *)(*(int *)(*state + 0x4a4) + 0x60);

                *(u16 *)(*(int *)(*state + 0x4a4) + 0x60) = (hw & ~0xff00) |
                    (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~1) << 0x18) >> 0x10);
            }
            ((B8 *)(*(int *)(*state + 0x488) + 8))->f &= ~2;
            ((B8 *)(*(int *)(*(int *)(*state + 0x4a4) + 0x488) + 8))->f &= ~2;
            {
                u16 hw = *(u16 *)(*(int *)(*state + 0x4a4) + 0x60);

                *(u16 *)(*(int *)(*state + 0x4a4) + 0x60) = (hw & ~0xff00) |
                    ((((((unsigned int)hw << 0x10) >> 0x18) | 0xc6) << 0x18) >> 0x10);
            }
            *(u16 *)(*(int *)(*state + 0x4a4) + 0x1ae) |= 1;
            func_ov107_020c5c54(*state, (Vec3 *)(*(int *)(*state + 0x4a4) + 0xb0));
        } else if (*(int *)(*state + 0x4ac) == 0) {
            *(short *)(*state + 0x4a0) = *(short *)(*state + 0x21a);
            *(int *)(*state + 0x4b0) = 0;
            {
                u16 hw = *(u16 *)(*state + 0x60);

                *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
                    (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~1) << 0x18) >> 0x10);
            }
            ((B8 *)(*(int *)(*state + 0x488) + 8))->f &= ~2;
            {
                u16 hw = *(u16 *)(*state + 0x60);

                *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
                    ((((((unsigned int)hw << 0x10) >> 0x18) | 0xc6) << 0x18) >> 0x10);
            }
            *(u16 *)(*state + 0x1ae) |= 1;
        }
        state[0x19] = 1;
        state[0x18] = 1;
        func_ov107_020c0b90(*state, 0x12, *(Vec3 *)state[0xe], 0);
        ((B8 *)(*(int *)(*state + 0x488) + 8))->f &= ~1;
        func_ov107_020c5af8(*state, 0x12d, 0x11, state[0xe]);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov237_020d09cc);
        return;
    }
}
