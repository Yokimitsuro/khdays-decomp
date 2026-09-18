/* Death entry of the ov284 enemy: sends the overlay's 4-byte message to the actor's +0x24 hook,
 * clears bit 0 and sets bits 1/7 of the +0x60 high byte, sets bits 0/1 of +0x1ae, clears bit 0
 * of the +0x3a8 item's +8 flags, fires reaction 0x16c mode 6 at the +4 anchor, requests
 * sub-state 0 and ends the state. */
typedef unsigned char u8;
typedef unsigned short u16;
struct hw60 { u16 lo : 8, hi : 8; };
struct bf { unsigned int b : 8; };
typedef struct { u16 id; u16 arg; } ShortMsg;

struct Ov284Owner {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov284Owner *self, ShortMsg *msg, int size);
};

extern void func_ov107_020c5af8(struct Ov284Owner *owner, int id, int mode, void *anchor);
extern void func_0203c634(int *node, int slot, void *cb);
extern const ShortMsg data_ov284_020cd5b4;

void func_ov284_020cd080(int *node)
{
    int *state = (int *)node[1];
    ShortMsg msg;

    msg = data_ov284_020cd5b4;
    if (((struct Ov284Owner *)*state)->pfnMessage != 0) {
        ((struct Ov284Owner *)*state)->pfnMessage((struct Ov284Owner *)*state, &msg, 4);
    }
    ((struct hw60 *)(*state + 0x60))->hi &= ~1;
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x82) << 0x18) >> 0x10));
    }
    *(u16 *)(*state + 0x100 + 0xae) |= 3;
    ((struct bf *)(*(int *)(*state + 0x3a8) + 8))->b &= ~1;
    func_ov107_020c5af8((struct Ov284Owner *)*state, 0x16c, 6, (void *)state[1]);
    *(u8 *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
