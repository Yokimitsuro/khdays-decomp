/*
 * func_ov287_020d0158 -- Ov287_Actor_SetSubStateAndNotify.
 *
 * Installed in the +0x1dc slot by func_ov287_020cfc04, shared with ov288 and ov289. Does
 * nothing unless the actor is in mode 1. Builds the fourteen-byte event packet that the +0x1c
 * handler's sub-opcode 4 branch expects -- kind 5, sub 4, the index biased by four times the
 * actor's +0x38c and folded into seven bits with the on flag in bit 7 -- sends it on channel 4,
 * then applies the same change locally: the raw index on channel 0 of the first subitem, the
 * biased index on channel 2, and a refresh.
 *
 * Ghidra: Ov287_Actor_SetSubStateAndNotify(Ov287Actor *pActor, int nIndex, int nOn), type
 * /khdays/ActorEventPacket, which /khdays/ActorEventMsg now embeds at offset 0.
 *
 * Byte-exact codegen notes (mwccarm 3.0/139):
 *  - The packet is cleared through a pointer and the id, sub and kind are written through that
 *    same pointer, which is why the original keeps one base register for all of them. Only the
 *    arg byte is written as a struct member and comes out sp-relative, exactly as here.
 *  - The on flag is folded in as `(u32)(on << 31) >> 24` with NO cast around it. Casting that
 *    term to u8 costs an extra `and r3, r3, #0xff`; left uncast, mwcc folds the shift into the
 *    `orr` operand as the original does.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct ActorEventPacket {
    u16 senderId;
    u8 kind;
    u8 sub;
    u8 arg;
    u8 payload[9];
};

struct Actor {
    char pad000[2];
    u16 id002;
    char pad004[0x4c];
    int mode050;
    char pad054[0x330];
    void *pSubitem384;
    char pad388[4];
    int bias38c;
};

extern void func_02031384(int channel, void *packet, int len);
extern void func_0203b9fc(void *subitem, int channel, int value, int on);
extern void func_0203c7ac(void *subitem, int channel);

void func_ov287_020d0158(struct Actor *actor, int index, int on)
{
    struct ActorEventPacket packet;
    u16 *p;
    int biased;

    if (actor->mode050 != 1) {
        return;
    }
    p = (u16 *)&packet;
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = 0;
    p[6] = 0;
    p[0] = actor->id002;
    ((u8 *)p)[3] = 4;
    ((u8 *)p)[2] = 5;
    packet.arg = (u8)((u8)(index + actor->bias38c * 4) & 0x7f | (u32)(on << 31) >> 24);
    func_02031384(4, &packet, 0xe);
    func_0203b9fc(actor->pSubitem384, 0, (short)index, on);
    biased = (short)(index + actor->bias38c * 4);
    func_0203b9fc(actor->pSubitem384, 2, biased, on);
    func_0203c7ac(actor->pSubitem384, 0);
}
