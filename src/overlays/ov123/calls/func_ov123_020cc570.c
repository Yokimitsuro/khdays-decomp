/* Hit handler of the ov123 enemy (and its byte-identical twin): ignored while the +0x21a
 * stamina is spent; the damage is resolved and the stamina drops by it (clamped to the +0x218
 * maximum); spent stamina on the owner asks for sub-state 3 and a 0x8000 hit for 5; a positive
 * damage that is not the 8|0x80/0x80 special toggles bit 0 of the state's +0x34 and fires
 * reaction 0x115 with the mode alternating (2/3 for flags 0x22, 0/1 otherwise) at the +0x14
 * position. */
extern int func_ov107_020c89e8();
extern void func_ov107_020c5af8(int obj, int id, unsigned short mode, int node);

typedef struct { int a, b, c; } Blk3;
struct NodeFacing { unsigned char facing : 1; };
struct HitFlags { unsigned int lo : 16, hi : 16; };

int func_ov123_020cc570(int this, int a1, int a2)
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

    if ((int)*(short *)(*(int *)p4 + 0x21a) == 0) {
        *(char *)(*(int *)p4 + 0x1c7) = 3;
    } else {
        if ((unsigned short)*(int *)a2 & 0x8000)
            *(char *)(*(int *)p4 + 0x1c7) = 5;
    }

    if (*(int *)(a2 + 0x28) > 0) {
        hf = (struct HitFlags *)a2;
        if ((hf->lo & 8) == 0 || (hf->lo & 0x80) == 0 || hf->hi != 0x80) {
            fb = (struct NodeFacing *)(p4 + 0xd);
            if (hf->lo & 0x22) {
                fb->facing = fb->facing + 1;
                func_ov107_020c5af8(this, 0x115, (fb->facing & 1) ? 2 : 3, *(int *)(p4 + 5));
            } else {
                fb->facing = fb->facing + 1;
                func_ov107_020c5af8(this, 0x115, (fb->facing & 1) ? 0 : 1, *(int *)(p4 + 5));
            }
        }
    }
    return 1;
}
