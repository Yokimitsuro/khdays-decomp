/* func_ov187_020d58a0 -- tick this enemy's stagger timer on a hit, stash the hit info, and flip
 * the node's facing bit.
 *
 * Same shape as TickStaggerAndFlipFacing (ov294/295/296) with three extras: a1 is
 * parked at p4[0x13], the hit's Vec3 at a2+4 is copied to p4+0x50, and a 0x8000 flag
 * in the hit word selects sub-state 5 instead of 3. Reaction id here is 0x120.
 *
 * The hit descriptor at a2 is a 32-bit flag word (bits 0-15 "lo") plus a 16-bit kind
 * ("hi") -- a bitfield container, NOT a u32 plus a (u16) cast: the bare `lsr #0x10`
 * with no paired `lsl` is the tell. See codegen-cracks.md. */
extern int func_ov107_020c89e8();
extern void func_ov107_020c5af8(int obj, int id, unsigned short mode, int node);

typedef struct { int a, b, c; } Blk3;
struct NodeFacing { unsigned char facing : 1; };
struct HitFlags { unsigned int lo : 16, hi : 16; };

int func_ov187_020d58a0(int this, int a1, int a2)
{
    int s = (int)*(short *)(this + 0x21a);
    int *p4 = *(int **)(this + 0x214);
    int n;
    int d;
    int result;
    struct HitFlags *hf;
    struct NodeFacing *fb;

    if (s <= 0)
        return 0;

    n = func_ov107_020c89e8(this, a2);
    *(int *)(a2 + 0x28) = n;

    d = (int)*(short *)(this + 0x21a) - n;
    if (d < 0) {
        result = 0;
    } else {
        result = (int)*(short *)(this + 0x218);
        if (d <= result)
            result = d;
    }
    *(short *)(this + 0x21a) = (short)result;

    *(int *)(p4 + 0x13) = a1;
    *(Blk3 *)((char *)p4 + 0x50) = *(Blk3 *)(a2 + 4);

    if ((int)*(short *)(this + 0x21a) == 0) {
        *(char *)(*(int *)p4 + 0x1c7) = 3;
    } else {
        if ((unsigned short)*(int *)a2 & 0x8000)
            *(char *)(*(int *)p4 + 0x1c7) = 5;
    }

    if (*(int *)(a2 + 0x28) > 0) {
        hf = (struct HitFlags *)a2;
        if ((hf->lo & 8) == 0 || (hf->lo & 0x80) == 0 || hf->hi != 0x80) {
            fb = (struct NodeFacing *)(p4 + 0x25);
            if (hf->lo & 0x22) {
                fb->facing = fb->facing + 1;
                func_ov107_020c5af8(this, 0x120, (fb->facing & 1) ? 2 : 3, *(int *)(p4 + 0x11));
            } else {
                fb->facing = fb->facing + 1;
                func_ov107_020c5af8(this, 0x120, (fb->facing & 1) ? 0 : 1, *(int *)(p4 + 0x11));
            }
        }
    }

    return 1;
}
