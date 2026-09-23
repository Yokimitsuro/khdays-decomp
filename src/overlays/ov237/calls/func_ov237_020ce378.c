/* Start move of the ov237 actor: the actor's +0x494 and +0x5c clear. Alone (no +0x4ac partner) it
 * appears at the +0x38 point offset by data_ov237_020d1bb8 turned toward the partner rig (020cdb50),
 * marks +0x4b0; either way bit 0 of the +0x60 high byte is set and bits 1, 2, 6 and 7 cleared, bit 0 of
 * +0x1ae cleared and bit 0 of the +0x488 rig's +8 flags set (a linked partner takes the actor's
 * health). +0x58 / +0x60 / +0x64 are set, the +0x28 timer rolls between the +0x224 and +0x228
 * bounds and the brain waits on 020ce584. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;

extern Vec3 func_ov237_020cdb50(int *node, Vec3 *target);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov107_020c5c54(int owner, const Vec3 *pos);
extern int func_02023eb4(int bound);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov237_020ce584(void);
extern const Vec3 data_ov237_020d1bb8;

void func_ov237_020ce378(int *node)
{
    int *state = (int *)node[1];
    Vec3 pos;
    Vec3 off;

    *(int *)(*state + 0x494) = 0;
    state[0x17] = 0;
    if (*(int *)(*state + 0x4ac) == 0) {
        pos = *(Vec3 *)state[0xe];
        off = data_ov237_020d1bb8;
        off = func_ov237_020cdb50(node, &off);
        VEC_Add(&pos, &off, &pos);
        *(int *)(*state + 0x4b0) = 1;
        func_ov107_020c5c54(*state, &pos);
        {
            u16 hw = *(u16 *)(*state + 0x60);

            *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
                ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
        }
        {
            u16 hw = *(u16 *)(*state + 0x60);

            *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
                (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0xc6) << 0x18) >> 0x10);
        }
        *(u16 *)(*state + 0x1ae) &= ~1;
        ((B8 *)(*(int *)(*state + 0x488) + 8))->f |= 1;
    } else {
        {
            u16 hw = *(u16 *)(*state + 0x60);

            *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
                ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
        }
        {
            u16 hw = *(u16 *)(*state + 0x60);

            *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
                (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0xc6) << 0x18) >> 0x10);
        }
        *(u16 *)(*state + 0x1ae) &= ~1;
        ((B8 *)(*(int *)(*state + 0x488) + 8))->f |= 1;
        *(short *)(*(int *)(*state + 0x4a4) + 0x21a) = *(short *)(*state + 0x21a);
    }
    state[0x18] = 1;
    state[0x19] = 1;
    state[0x16] = 1;
    {
        int lo = *(int *)(*state + 0x224);
        int span = *(int *)(*state + 0x228) - lo;

        if (span < 0) {
            span = -span;
        }
        state[0xa] = lo + func_02023eb4(span + 1);
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov237_020ce584);
}
