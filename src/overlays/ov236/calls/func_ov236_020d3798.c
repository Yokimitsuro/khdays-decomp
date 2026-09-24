/* Hit filter of the ov236 rider pair (+0x1d0), active while its +0x21a stock is positive and the
 * actor is not in move 8. With the +0x3d4 guard raised the hit only zeroes its damage and raises
 * bit 0 of its result word. Otherwise the first rider (+0x3c0 part, +0x3d0 stock) that is still up
 * and was struck takes the full damage (020c89e8, floored at 0); when it falls, the short note
 * data_ov236_020d6430 (rider 2 / 3) goes to the actor's +0x24 hook, the 14-byte message
 * data_ov236_020d6462 (3 when the other rider is down too, else 2) carries the attacker's point to
 * the +0x384 object's hook, reaction 0x127 mode 0xe fires there and the part's bit 1 is raised. The
 * stock becomes the riders' sum (clamped to +0x218) and at 0 the actor requests move 0xb. A damaging
 * hit that is not the 8|0x80/0x80 special flips the +0x7d parity and fires reaction 0x127 with mode
 * 2/3 (bits 1/5) or 0/1 at the attacker's point. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int value; } Fx32;
typedef struct { u16 id; u8 kind; u8 cmd; u8 flag; u8 pos[9]; } Cmd14;
typedef struct { u16 id; u8 kind; u8 cmd; } Note4;

struct HitWord { unsigned int lo : 16, hi : 16; };
struct Parity { u8 b0 : 1; };
typedef struct { int b0 : 1; } Flag1;
struct PartFlags { unsigned int lo : 8; };
struct Ov236 {
    char pad000[0x3c0];
    int riders[2];          /* +0x3c0 */
    char pad3c8[0x3d0 - 0x3c8];
    short riderStock[2];    /* +0x3d0 */
};
#define RIDERS(s) ((struct Ov236 *)*(s))

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

extern int func_ov107_020c89e8(int item, unsigned int *hit);
extern void func_ov107_020c5af8(char *self, int id, u16 mode, void *at);
extern const Note4 data_ov236_020d6430;
extern const Cmd14 data_ov236_020d6462;

int func_ov236_020d3798(char *self, int src, unsigned int *hit)
{
    long i;
    int *state = *(int **)(self + 0x214);
    Cmd14 msg;
    Note4 note;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    int sum;
    int limit;

    if (*(short *)(self + 0x200 + 0x1a) <= 0) {
        return 0;
    }
    if (*(signed char *)(*state + 0x100 + 0xc6) == 8) {
        return 0;
    }
    if (!((Flag1 *)(*state + 0x3d4))->b0) {
        for (i = 0; i < 2; i++) {
            if (RIDERS(state)->riderStock[i] > 0 && hit[6] == (unsigned int)RIDERS(state)->riders[i]) {
                hit[10] = func_ov107_020c89e8(*(int *)(*state + 0x384), hit);
                ((short *)(*state + 0x3d0))[i] -= hit[10];
                if (RIDERS(state)->riderStock[i] < 0) {
                    RIDERS(state)->riderStock[i] = 0;
                }
                if (RIDERS(state)->riderStock[i] == 0) {
                    note = data_ov236_020d6430;
                    note.cmd = i == 0 ? 2 : 3;
                    if (*(void (**)(int, Note4 *, int))(*state + 0x24) != 0) {
                        (*(void (**)(int, Note4 *, int))(*state + 0x24))(*state, &note, 4);
                    }
                    msg = data_ov236_020d6462;
                    msg.flag = RIDERS(state)->riderStock[(i + 1) % 2] == 0 ? 3 : 2;
                    {
                        char *at = *(char **)hit[6];

                        PACK(msg, scratchX, *(Fx32 *)(at + 4), 5);
                        PACK(msg, scratchY, *(Fx32 *)(at + 8), 8);
                        PACK(msg, scratchZ, *(Fx32 *)(at + 0xc), 11);
                    }
                    if (*(void (**)(int, Cmd14 *, int))(*(int *)(*state + 0x384) + 0x24) != 0) {
                        (*(void (**)(int, Cmd14 *, int))(*(int *)(*state + 0x384) + 0x24))(*(int *)(*state + 0x384), &msg, 0xe);
                    }
                    func_ov107_020c5af8(self, 0x127, 0xe, (void *)(*(int *)hit[6] + 4));
                    ((struct PartFlags *)(RIDERS(state)->riders[i] + 8))->lo |= 2;
                }
                break;
            }
        }
        sum = RIDERS(state)->riderStock[0] + RIDERS(state)->riderStock[1];
        if (sum < 0) {
            limit = 0;
        } else {
            limit = *(short *)(self + 0x200 + 0x18);
            if (sum <= limit) {
                limit = sum;
            }
        }
        *(short *)(self + 0x200 + 0x1a) = limit;
        if (*(short *)(self + 0x200 + 0x1a) == 0) {
            *(u8 *)(*state + 0x1c7) = 0xb;
        }
        if ((int)hit[10] > 0) {
            if (!((((struct HitWord *)hit)->lo & 8) != 0 && (((struct HitWord *)hit)->lo & 0x80) != 0 && ((struct HitWord *)hit)->hi == 0x80)) {
                if ((((struct HitWord *)hit)->lo & 0x22) != 0) {
                    ((struct Parity *)((u8 *)state + 0x7d))->b0++;
                    func_ov107_020c5af8(self, 0x127, (((struct Parity *)((u8 *)state + 0x7d))->b0 & 1) ? 2 : 3, (void *)(*(int *)hit[6] + 4));
                } else {
                    ((struct Parity *)((u8 *)state + 0x7d))->b0++;
                    func_ov107_020c5af8(self, 0x127, (((struct Parity *)((u8 *)state + 0x7d))->b0 & 1) ? 0 : 1, (void *)(*(int *)hit[6] + 4));
                }
            }
        }
    } else {
        hit[10] = 0;
        ((struct HitWord *)(hit + 9))->lo |= 1;
    }
    return 1;
}
