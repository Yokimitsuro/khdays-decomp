/*
 * func_ov107_020c0b90 -- send a kind-5 position message.
 *
 * Builds a 14-byte message: the object's u16 id, kind 5, the caller's command
 * byte and flag byte, then the position packed into three 24-bit big-endian
 * coordinates; sends it through func_02031258 on channel 1.
 *
 * The position is kept next to the message in one stack struct; the message's
 * address escapes into the send call, so mwcc keeps the three position stores
 * the ROM has.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct { int x, y, z; } VecFx32;
typedef struct { u8 hi, mid, lo; } Fx24;   /* sign + 23-bit magnitude, big-endian */

typedef struct {
    u16 id;             /* +0x0 */
    u8 kind;            /* +0x2 */
    u8 cmd;             /* +0x3 */
    u8 flag;            /* +0x4 */
    Fx24 pos[3];        /* +0x5 */
} PosMsg;

typedef struct {
    VecFx32 pos;
    PosMsg msg;
} PosSend;

struct MsgOwner {
    char pad0[2];
    u16 id;             /* +0x2 */
};

extern int func_02031258(int channel, u16 *msg, u16 size);

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

void func_ov107_020c0b90(struct MsgOwner *obj, int cmd, VecFx32 pos, u8 flag) {
    PosSend send;
    PosMsg *msg = &send.msg;
    u16 *words = (u16 *)msg;

    words[0] = 0;
    words[1] = 0;
    words[2] = 0;
    words[3] = 0;
    words[4] = 0;
    words[5] = 0;
    words[6] = 0;
    msg->id = obj->id;
    msg->cmd = cmd;
    msg->kind = 5;

    send.pos.x = pos.x;
    PackFx24(&send.msg.pos[0], send.pos.x);
    send.pos.y = pos.y;
    PackFx24(&send.msg.pos[1], send.pos.y);
    send.pos.z = pos.z;
    PackFx24(&send.msg.pos[2], send.pos.z);
    send.msg.flag = flag;

    func_02031258(1, (u16 *)&send.msg, sizeof(PosMsg));
}
