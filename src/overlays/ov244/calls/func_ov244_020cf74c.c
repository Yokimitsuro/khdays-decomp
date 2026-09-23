/* Hit filter of the ov244 enemy (installed at +0x1d0), active while its +0x21a stock is positive. The
 * damage (020c89e8) is doubled when the hit body is its +0x39c core, the stock drops by it
 * (clamped to 0..+0x218), and a damaging hit that is not the 8|0x80/0x80 special flips the +8
 * parity and fires reaction 0x113 with mode 2/3 (bits 1/5) or 0/1 at the hit body's +4 point (the
 * +0x74 position of the +0x214 state's actor without one). Once that actor's stock is empty it
 * requests move 3. */
typedef unsigned char u8;
typedef unsigned short u16;

struct HitWord { unsigned int lo : 16, hi : 16; };
struct Parity { u8 b0 : 1; };

extern int func_ov107_020c89e8(char *self, unsigned int *hit);
extern void func_ov107_020c5af8(char *self, int id, u16 mode, void *at);

int func_ov244_020cf74c(char *self, int src, unsigned int *hit)
{
    int *state = *(int **)(self + 0x214);
    void *at;
    int stock;
    int limit;

    if (*(short *)(self + 0x200 + 0x1a) <= 0) {
        return 0;
    }
    if (hit[6] != 0) {
        at = (void *)(*(int *)hit[6] + 4);
    } else {
        at = (void *)(*state + 0x74);
    }
    hit[10] = func_ov107_020c89e8(self, hit);
    if (*(unsigned int *)(*state + 0x39c) == hit[6]) {
        hit[10] *= 2;
    }
    stock = *(short *)(self + 0x200 + 0x1a) - hit[10];
    if (stock < 0) {
        limit = 0;
    } else {
        limit = *(short *)(self + 0x200 + 0x18);
        if (stock <= limit) {
            limit = stock;
        }
    }
    *(short *)(self + 0x200 + 0x1a) = limit;
    if ((int)hit[10] > 0) {
        if (!((((struct HitWord *)hit)->lo & 8) != 0 && (((struct HitWord *)hit)->lo & 0x80) != 0 && ((struct HitWord *)hit)->hi == 0x80)) {
            if ((((struct HitWord *)hit)->lo & 0x22) != 0) {
                ((struct Parity *)((u8 *)state + 8))->b0++;
                func_ov107_020c5af8(self, 0x113, (((struct Parity *)((u8 *)state + 8))->b0 & 1) ? 2 : 3, at);
            } else {
                ((struct Parity *)((u8 *)state + 8))->b0++;
                func_ov107_020c5af8(self, 0x113, (((struct Parity *)((u8 *)state + 8))->b0 & 1) ? 0 : 1, at);
            }
        }
    }
    if (*(short *)(*state + 0x200 + 0x1a) == 0) {
        *(u8 *)(*state + 0x1c7) = 3;
    }
    return 1;
}
