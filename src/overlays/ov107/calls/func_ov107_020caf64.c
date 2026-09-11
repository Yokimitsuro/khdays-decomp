typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u16 id;
    u8 skip;
    u8 field_03;
    u8 level;
} Query;

struct Actor;
typedef void (*RefreshFn)(struct Actor *actor, Query *q, int arg);

typedef struct Actor {
    u8 pad0[0x1c];
    RefreshFn refresh;
    u8 pad20[0x60 - 0x20];
    u16 state;
} Actor;

extern void func_ov107_020c0d94(Actor *actor, Query *q, int arg);

void func_ov107_020caf64(Actor *actor, Query *q, int arg) {
    if (q->skip == 0) {
        q->level = (u8)(((unsigned int)actor->state << 0x10) >> 0x18);
        if (actor->refresh != 0) {
            actor->refresh(actor, q, arg);
        }
    }
    func_ov107_020c0d94(actor, q, arg);
}
