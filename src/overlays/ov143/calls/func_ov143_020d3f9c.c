/* Tick this actor's stagger on a hit, stash the hit info, and flip the node's
 * facing bit (Ghidra: Ov143_ApplyHit).
 *
 * The same shape as the ov117 handler at the matching address, with this
 * actor's own offsets: the attacker is parked at node+0x38, the hit's Vec3 at
 * a2+4 lands on node+0x24, the facing bit lives in the byte at node+0x49, the
 * sound is placed on node+0x3c, and a 0x8000 flag in the hit word selects
 * sub-state 7 rather than 5. Reaction id here is 0x11e, which unlike ov117's
 * 0x120 is not an ARM immediate -- that one literal pool word is the whole
 * four-byte difference between the two functions.
 *
 * The hit descriptor at a2 is a 32-bit flag word (bits 0-15 "lo") plus a 16-bit
 * kind ("hi") -- a bitfield container, NOT a u32 plus a (u16) cast: the bare
 * `lsr #0x10` with no paired `lsl` is the tell.
 */
extern int func_ov107_020c89e8();
extern void func_ov107_020c5af8(int obj, int id, unsigned short mode, int node);

typedef struct { int a, b, c; } Blk3;
struct NodeFacing { unsigned char facing : 1; };
struct HitFlags { unsigned int lo : 16, hi : 16; };

int func_ov143_020cc71c(int this, int a1, int a2)
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

    *(int *)(p4 + 0xe) = a1;
    *(Blk3 *)((char *)p4 + 0x24) = *(Blk3 *)(a2 + 4);

    if (*(int *)(a2 + 0x28) > 0) {
        hf = (struct HitFlags *)a2;
        if ((hf->lo & 8) == 0 || (hf->lo & 0x80) == 0 || hf->hi != 0x80) {
            fb = (struct NodeFacing *)((char *)p4 + 0x49);
            if (hf->lo & 0x22) {
                fb->facing = fb->facing + 1;
                func_ov107_020c5af8(this, 0x11e, (fb->facing & 1) ? 2 : 3, *(int *)(p4 + 0xf));
            } else {
                fb->facing = fb->facing + 1;
                func_ov107_020c5af8(this, 0x11e, (fb->facing & 1) ? 0 : 1, *(int *)(p4 + 0xf));
            }
        }
    }

    return 1;
}
