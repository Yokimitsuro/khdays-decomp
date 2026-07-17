/* func_ov294_020d1c4c -- tick this enemy's stagger timer (+0x21a) and, when a hit lands, flip
 * the node's facing bit and fire reaction 0x171.
 *
 * The timer drains by the amount func_ov107_020c89e8 charges for the hit, clamped
 * to +0x218 and floored at 0; draining it fully puts the node in sub-state 3. The
 * hit descriptor at param_3 is a 32-bit flag word (bits 0-15 "lo") followed by a
 * 16-bit kind ("hi"); the reaction is skipped outright for kind 0x80 hits that
 * carry both flag 8 and flag 0x80. Flag 0x22 (in lo) picks which pair of reaction
 * modes is used: 2/3 with it, 0/1 without, chosen by the node's NEW facing bit.
 * param_3[10] carries the charged amount back out to the caller. */
extern int func_ov107_020c89e8(int obj, int src);
extern void func_ov107_020c5af8(int obj, int id, unsigned short mode, int node);

struct NodeFacing { unsigned char facing : 1; };
struct HitFlags { unsigned int lo : 16, hi : 16; };

int func_ov294_020d1c4c(int param_1, int param_2, unsigned int *param_3) {
    int *node = *(int **)(param_1 + 0x214);
    int taken;
    int delta;
    int rem;
    struct HitFlags *hf;
    struct NodeFacing *fb;

    if (*(short *)(param_1 + 0x21a) <= 0) {
        return 0;
    }
    taken = func_ov107_020c89e8(param_1, (int)param_3);
    param_3[10] = taken;
    delta = *(short *)(param_1 + 0x21a) - taken;
    if (delta < 0) {
        rem = 0;
    } else {
        rem = *(short *)(param_1 + 0x218);
        if (delta <= rem) {
            rem = delta;
        }
    }
    *(short *)(param_1 + 0x21a) = (short)rem;
    if (*(short *)(param_1 + 0x21a) == 0) {
        *(unsigned char *)(*node + 0x1c7) = 3;
    }
    if ((int)param_3[10] > 0) {
        hf = (struct HitFlags *)param_3;
        if ((hf->lo & 8) == 0 || (hf->lo & 0x80) == 0 || hf->hi != 0x80) {
            fb = (struct NodeFacing *)((char *)node + 0xc);
            if ((hf->lo & 0x22) != 0) {
                fb->facing = fb->facing + 1;
                func_ov107_020c5af8(param_1, 0x171, (fb->facing & 1) ? 2 : 3, node[1]);
            } else {
                fb->facing = fb->facing + 1;
                func_ov107_020c5af8(param_1, 0x171, (fb->facing & 1) ? 0 : 1, node[1]);
            }
        }
    }
    return 1;
}
