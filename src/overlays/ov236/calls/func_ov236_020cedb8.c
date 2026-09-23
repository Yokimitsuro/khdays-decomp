/* Hit filter of the ov236 mount (+0x1d0), active while its +0x21a stock is positive, the +0x54
 * invulnerability timer is out, the actor is not in move 9 and not guarding (+0x1ac bit 0).
 * - Move 0xc, hit on the +0x3a8 core: full damage (020c89e8), stock clamped to 0..+0x218; when it
 *   empties the actor stops at its current position (+0x190 = +0xb0) and requests move 3.
 * - While both riders are gone (no +0x3c0 / +0x3d4 presence, +0x3bd clear) or in move 8: the hit
 *   only raises bit 0 of its result word.
 * - Stock at 1: with both riders busy the actor requests move 0xc; a core hit requests move 8
 *   unless already in move 8 or 5.
 * - Moves 2 / 6 / 7: a quarter of the damage (at least 1 unless flag 0x800), stock floored at 1,
 *   and every tenth of +0x218 accumulated in +0x58 raises the +0x52 stagger flag.
 * - Move 5: half damage (a core hit also raises +0x52 bit 1), stock clamped and floored at 1.
 * In moves 0xb (and 0xa with +0x3bd set) non-flag-0x10 hits take half damage, and core hits with
 * flag 0x20 or any flag-0x10 hit bounce the actor off the attacker: the +0x3c velocity is
 * reflected about the direction from the +0x34 point to the attacker (speed 0.5), flag 0x10 also
 * sets +0x1ae bit 0 and 1.0 of invulnerability, and every fourth bounce requests move 0xc.
 * A damaging hit that is not the 8|0x80/0x80 special flips the +0x50 parity and fires reaction
 * 0x127 with mode 2/3 (bits 1/5) or 0/1 at the +0x38 point. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

struct HitWord { unsigned int lo : 16, hi : 16; };
struct Parity { u8 b0 : 1; };
struct Bits52 { u8 b0 : 1; u8 b1 : 1; };
typedef struct { int b0 : 1; } Flag1;

extern int func_ov107_020c89e8(char *self, unsigned int *hit);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern int VEC_Mag(const Vec3 *v);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern void func_ov107_020c5af8(char *self, int id, u16 mode, void *at);

int func_ov236_020cedb8(char *self, int src, unsigned int *hit)
{
    int *state = *(int **)(self + 0x214);
    Vec3 away;
    Vec3 back;
    Vec3 bounce;
    Vec3 dir;
    int front;
    int rear;
    int frontFree;
    int rearFree;
    int stock;
    int limit;

    front = *(int *)(*state + 0x3b4);
    rear = *(int *)(*state + 0x3b8);
    frontFree = (*(u16 *)(front + 0x1ac) & 2) == 0;
    rearFree = (*(u16 *)(rear + 0x1ac) & 2) == 0;
    if (*(short *)(self + 0x200 + 0x1a) <= 0) {
        return 0;
    }
    if (state[0x15] > 0) {
        return 0;
    }
    if (*(signed char *)(*state + 0x100 + 0xc6) == 9) {
        return 0;
    }
    if ((*(u16 *)(*state + 0x100 + 0xac) & 1) != 0) {
        return 0;
    }
    hit[10] = 0;
    if (*(signed char *)(*state + 0x100 + 0xc6) == 0xc && hit[6] == *(unsigned int *)(*state + 0x3a8)) {
        hit[10] = func_ov107_020c89e8(self, hit);
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
        if (*(short *)(self + 0x200 + 0x1a) == 0) {
            *(Vec3 *)(*state + 0x190) = *(Vec3 *)(*state + 0xb0);
            *(u8 *)(*state + 0x1c7) = 3;
        }
    } else if ((!((Flag1 *)(front + 0x3c0))->b0 && !((Flag1 *)(rear + 0x3d4))->b0 && *(u8 *)(*state + 0x3bd) == 0) ||
               *(signed char *)(*state + 0x100 + 0xc6) == 8) {
        if (src != 0) {
            VEC_Subtract((void *)(src + 0x74), (void *)(*(int *)(*state + 0x398) + 0x20), &away);
            ((struct HitWord *)(hit + 9))->lo |= 1;
        }
    } else if (*(short *)(self + 0x200 + 0x1a) == 1) {
        if (!frontFree && !rearFree && *(signed char *)(*state + 0x100 + 0xc6) != 0xc) {
            *(u8 *)(*state + 0x1c7) = 0xc;
        } else if (hit[6] == *(unsigned int *)(*state + 0x3a8)) {
            if (*(signed char *)(*state + 0x100 + 0xc6) != 8 && *(signed char *)(*state + 0x100 + 0xc6) != 5) {
                *(u8 *)(*state + 0x1c7) = 8;
            }
        }
    } else if (!(*(signed char *)(*state + 0x100 + 0xc6) != 2 && *(signed char *)(*state + 0x100 + 0xc6) != 6 &&
                 *(signed char *)(*state + 0x100 + 0xc6) != 7)) {
        hit[10] = func_ov107_020c89e8(self, hit) >> 2;
        if ((((struct HitWord *)hit)->lo & 0x800) == 0 && (int)hit[10] < 1) {
            hit[10] = 1;
        }
        *(short *)(self + 0x200 + 0x1a) -= hit[10];
        if (*(short *)(self + 0x200 + 0x1a) < 1) {
            *(short *)(self + 0x200 + 0x1a) = 1;
        }
        *(short *)((u8 *)state + 0x58) += hit[10];
        if (*(short *)((u8 *)state + 0x58) >= *(short *)(self + 0x200 + 0x18) / 10) {
            *(short *)((u8 *)state + 0x58) = 0;
            ((struct Bits52 *)((u8 *)state + 0x52))->b0 = 1;
        }
    } else if (*(signed char *)(*state + 0x100 + 0xc6) == 5) {
        if (hit[6] == *(unsigned int *)(*state + 0x3a8)) {
            *((u8 *)state + 0x52) |= 2;
        }
        hit[10] = func_ov107_020c89e8(self, hit) >> 1;
        if ((((struct HitWord *)hit)->lo & 0x800) == 0 && (int)hit[10] < 1) {
            hit[10] = 1;
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
        if (*(short *)(self + 0x200 + 0x1a) < 1) {
            *(short *)(self + 0x200 + 0x1a) = 1;
        }
    }
    if (*(signed char *)(*state + 0x100 + 0xc6) == 0xb ||
        (*(signed char *)(*state + 0x100 + 0xc6) == 0xa && *(u8 *)(*state + 0x3bd) != 0)) {
        if ((((struct HitWord *)hit)->lo & 0x10) == 0) {
            hit[10] = func_ov107_020c89e8(self, hit) >> 1;
            if ((((struct HitWord *)hit)->lo & 0x800) == 0 && (int)hit[10] < 1) {
                hit[10] = 1;
            }
            *(short *)(self + 0x200 + 0x1a) -= hit[10];
            if (*(short *)(self + 0x200 + 0x1a) < 1) {
                *(short *)(self + 0x200 + 0x1a) = 1;
            }
        }
        if ((hit[6] == *(unsigned int *)(*state + 0x3a8) && (((struct HitWord *)hit)->lo & 0x20) != 0) ||
            (((struct HitWord *)hit)->lo & 0x10) != 0) {
            *((signed char *)state + 0x53) += 1;
            if ((((struct HitWord *)hit)->lo & 0x10) != 0) {
                *(u16 *)(*state + 0x100 + 0xae) |= 1;
                state[0x15] = 0x1000;
            }
            VEC_Subtract((void *)(src + 0x74), (void *)state[0xd], &dir);
            dir.y = 0;
            func_01ff8d18(&dir, &dir);
            VEC_Mag((Vec3 *)(state + 0xf));
            func_01ffa724(-0x1000, (Vec3 *)(state + 0xf), &back);
            func_01ffa724(VEC_DotProduct(&back, &dir) * 2, &dir, &bounce);
            VEC_Subtract(&bounce, &back, &bounce);
            bounce.y = 0;
            func_01ff8d18(&bounce, (Vec3 *)(state + 0xf));
            func_01ffa724(0x800, (Vec3 *)(state + 0xf), (Vec3 *)(state + 0xf));
            if (*((signed char *)state + 0x53) >= 4) {
                *((signed char *)state + 0x53) = 0;
                *(u8 *)(*state + 0x1c7) = 0xc;
            }
        }
    }
    if ((int)hit[10] > 0) {
        if (!((((struct HitWord *)hit)->lo & 8) != 0 && (((struct HitWord *)hit)->lo & 0x80) != 0 && ((struct HitWord *)hit)->hi == 0x80)) {
            if ((((struct HitWord *)hit)->lo & 0x22) != 0) {
                ((struct Parity *)((u8 *)state + 0x50))->b0++;
                func_ov107_020c5af8(self, 0x127, (((struct Parity *)((u8 *)state + 0x50))->b0 & 1) ? 2 : 3, (void *)state[0xe]);
            } else {
                ((struct Parity *)((u8 *)state + 0x50))->b0++;
                func_ov107_020c5af8(self, 0x127, (((struct Parity *)((u8 *)state + 0x50))->b0 & 1) ? 0 : 1, (void *)state[0xe]);
            }
        }
    }
    return 1;
}
