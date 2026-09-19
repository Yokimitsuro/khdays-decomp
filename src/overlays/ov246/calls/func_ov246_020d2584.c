/* Send the ov246 enemy's position message: the overlay's 14-byte template (data_ov246_020d30f8)
 * with the +4 point packed into bytes 5..13 as 24-bit fixed values (each copied through a stack
 * Fx32 first) and byte 4 set when the owner's +0x13c height is more than 0x100 above 0x1000, sent
 * through the owner's +0x24 hook (length 0xe). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;
typedef struct { u8 hi, mid, lo; } Fx24;

typedef struct {
    u16 id;             /* +0x0 */
    u8 kind;            /* +0x2 */
    u8 cmd;             /* +0x3 */
    u8 flag;            /* +0x4 */
    Fx24 pos[3];        /* +0x5 */
} PosMsg;

extern const PosMsg data_ov246_020d30f8;

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

void func_ov246_020d2584(int *state)
{
    PosMsg msg;
    FxVec vContact;
    FxVec *pPos;

    msg = data_ov246_020d30f8;
    pPos = (FxVec *)state[1];
    vContact.x = pPos->x;
    PackFx24(&msg.pos[0], vContact.x.value);
    vContact.y = pPos->y;
    PackFx24(&msg.pos[1], vContact.y.value);
    vContact.z = pPos->z;
    PackFx24(&msg.pos[2], vContact.z.value);
    if (*(int *)(*state + 0x13c) - 0x1000 > 0x100) {
        msg.flag = 1;
    }
    if (*(void (**)(int, PosMsg *, int))(*state + 0x24) != 0) {
        (*(void (**)(int, PosMsg *, int))(*state + 0x24))(*state, &msg, 0xe);
    }
}
