/* Tick this enemy's stagger timer on a hit, stash the hit info and flip the node's
 * facing bit. Same shape as func_ov185_020ce40c, with different sub-state ids
 * (3 when the timer runs out, 7 on the 0x8000 hit flag), the hit's Vec3 copied to
 * p4+0x24, the hit owner parked at p4+0x38, and reaction id 0x14e.
 *
 * The hit descriptor at a2 is a bitfield container: a 16-bit flag word plus a
 * 16-bit kind. The bare `lsr #0x10` with no paired `lsl` is the tell. The gate at
 * a2+0x10 reads its low half SIGNED, hence the lsl/asr pair. */
extern int func_ov107_020c89e8();
extern void func_ov107_020c5af8(int obj, int id, unsigned short mode, int node);

typedef struct { int a, b, c; } Blk3;
struct NodeFacing { unsigned char facing : 1; };
struct HitFlags { unsigned int lo : 16, hi : 16; };
struct HitGate { int lo : 16, hi : 16; };

int func_ov149_020ce538(int this, int a1, int a2)
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

    if ((int)*(short *)(this + 0x21a) == 0) {
        *(char *)(*(int *)p4 + 0x1c7) = 3;
    } else {
        if ((unsigned short)*(int *)a2 & 0x8000)
            *(char *)(*(int *)p4 + 0x1c7) = 7;
    }

    *(int *)((char *)p4 + 0x38) = a1;
    *(Blk3 *)((char *)p4 + 0x24) = *(Blk3 *)(a2 + 4);

    if (((struct HitGate *)(a2 + 0x10))->lo > 0) {
        hf = (struct HitFlags *)a2;
        if ((hf->lo & 8) == 0 || (hf->lo & 0x80) == 0 || hf->hi != 0x80) {
            fb = (struct NodeFacing *)((char *)p4 + 0x49);
            if (hf->lo & 0x22) {
                fb->facing = fb->facing + 1;
                func_ov107_020c5af8(this, 0x14e, (fb->facing & 1) ? 2 : 3,
                                    *(int *)((char *)p4 + 0x3c));
            } else {
                fb->facing = fb->facing + 1;
                func_ov107_020c5af8(this, 0x14e, (fb->facing & 1) ? 0 : 1,
                                    *(int *)((char *)p4 + 0x3c));
            }
        }
    }

    return 1;
}
