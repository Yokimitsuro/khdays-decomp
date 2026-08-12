/*
 * func_ov120_020cc2a4 -- Ov120_Actor_HandleEvent.
 *
 * The actor class event handler installed in the +0x1c onAction slot by the ov120 initializer,
 * shared byte-for-byte with ov121 and ov122 (only the five call targets differ). Kind 5
 * dispatches on the sub-opcode; every path then forwards the event to the ov107 base handler.
 *
 *   0  start the first node slot's subitem through ov107::020c08cc at weight 0x999, passing the
 *      message packet's own payload bytes, and keep the returned handle in that slot
 *   1  take a private copy of the actor's bone transform, scale it by the same 0x999 weight and
 *      start the second slot's subitem from that transform
 *   2  pack the actor's current translation into a nine-byte payload -- three components, each
 *      as sign plus 23-bit magnitude split high/middle/low -- and start the third slot's subitem
 *      from it, again at weight 0x999
 *
 * Ghidra: Ov120_Actor_HandleEvent(Ov120Actor *pActor, ActorEventMsg *pMsg, uint uParam), types
 * /khdays/Ov120Actor, /khdays/Ov120NodeSlot, /khdays/Ov120BoneXform, /khdays/Vec3,
 * /khdays/PackedFx24 and /khdays/ActorEventPacket.
 *
 * Byte-exact codegen notes (mwccarm 3.0/139):
 *  - ov107::020c08cc TAKES SIX ARGUMENTS, NOT NINE. Its prologue is `push {r4-r8,lr}` plus
 *    `sub sp, #0x48`, so its incoming stack slots start at sp+0x60, and it reads exactly two of
 *    them: the weight at +0x60 and the payload pointer at +0x64. The three words the original
 *    also leaves at sp+8, sp+0xc and sp+0x10 are therefore NOT arguments -- they are a local
 *    twelve-byte copy of the translation that nothing ever reads. Modelling them as three extra
 *    call arguments costs three live values across the packing, which pushes the parameters down
 *    from r5-r7 to r4-r6 and makes the whole tail of the case schedule differently. Ghidra's
 *    decompiler makes the same wrong guess, because the call is unresolved on its side.
 *  - THE DEAD COPY MUST BE COPIED ONE WORD AT A TIME. mwcc does not dead-store-eliminate a
 *    struct assignment but it does eliminate scalar ones, so `v.x = ...` drops all three stores
 *    and the function comes out twelve bytes short. Copying through a one-word struct keeps the
 *    stores and lets mwcc fuse each one with the packing: one load per component, packed out of
 *    that register, then stored to the dead copy -- exactly what the original does. Same crack
 *    as the ov149 position broadcaster.
 *  - The payload buffer is declared first and the dead vector last; that is what puts the
 *    outgoing arguments at sp+0, the vector at sp+8, the transform at sp+0x14 and the payload at
 *    sp+0x40 in a 0x4c-byte frame.
 *  - Within a component the bytes are written high, middle, low -- ascending address order.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Ov120NodeSlot {
    void *pSubitem;
    void *pResult;
};

struct Vec3 {
    int x;
    int y;
    int z;
};

struct Ov120BoneXform {
    int aRotation[4];
    struct Vec3 vTranslation;
    int aScale[3];
    u8 bFlags;
    u8 aPad29[3];
};

/* one translation component on the wire: sign + 23-bit magnitude, high byte first */
struct PackedFx24 {
    u8 hi;
    u8 mid;
    u8 lo;
};

/* a single word; copying through it is what keeps the dead vector store alive */
struct Word {
    int w;
};

struct Ov120Actor {
    char pad000[0x3c];
    void *taskList;
    char pad040[0x60];
    struct Ov120BoneXform xfm;
    char pad0cc[0x2d8];
    struct Ov120NodeSlot *pNodeSlots;
};

struct ActorEventPacket {
    u16 wSenderId;
    u8 bKind;
    u8 bSub;
    u8 bArg;
    u8 aPayload[9];
};

struct ActorEventMsg {
    struct ActorEventPacket packet;
};

extern void func_0203ca9c(struct Ov120BoneXform *xform, int weight);
extern void *func_ov107_020c0794(void *taskList, void *subitem, int mode, int blend,
                                 struct Ov120BoneXform *xform);
extern void *func_ov107_020c08cc(void *taskList, void *subitem, int mode, int blend,
                                 int weight, void *payload);
extern void func_ov107_020c7500(struct Ov120Actor *actor, struct ActorEventMsg *msg, u32 param);

void func_ov120_020cc2a4(struct Ov120Actor *actor, struct ActorEventMsg *msg, u32 param)
{
    struct PackedFx24 aPayload[3];
    struct Ov120BoneXform xfmCopy;
    struct Vec3 vTranslationCopy;

    if (msg->packet.bKind == 5) {
        switch (msg->packet.bSub) {
        case 0:
            actor->pNodeSlots[0].pResult =
                func_ov107_020c08cc(actor->taskList, actor->pNodeSlots[0].pSubitem,
                                    5, 0, 0x999, msg->packet.aPayload);
            break;
        case 1:
            xfmCopy = actor->xfm;
            func_0203ca9c(&xfmCopy, 0x999);
            actor->pNodeSlots[1].pResult =
                func_ov107_020c0794(actor->taskList, actor->pNodeSlots[1].pSubitem,
                                    5, 0, &xfmCopy);
            break;
        case 2:
            *(struct Word *)&vTranslationCopy.x = *(struct Word *)&actor->xfm.vTranslation.x;
            aPayload[0].hi = (u8)((((u32)vTranslationCopy.x >> 0x10) & 0x7f) |
                                  (((u32)vTranslationCopy.x >> 0x18) & 0x80));
            aPayload[0].mid = (u8)((u32)vTranslationCopy.x >> 8);
            aPayload[0].lo = (u8)vTranslationCopy.x;

            *(struct Word *)&vTranslationCopy.y = *(struct Word *)&actor->xfm.vTranslation.y;
            aPayload[1].hi = (u8)((((u32)vTranslationCopy.y >> 0x10) & 0x7f) |
                                  (((u32)vTranslationCopy.y >> 0x18) & 0x80));
            aPayload[1].mid = (u8)((u32)vTranslationCopy.y >> 8);
            aPayload[1].lo = (u8)vTranslationCopy.y;

            *(struct Word *)&vTranslationCopy.z = *(struct Word *)&actor->xfm.vTranslation.z;
            aPayload[2].hi = (u8)((((u32)vTranslationCopy.z >> 0x10) & 0x7f) |
                                  (((u32)vTranslationCopy.z >> 0x18) & 0x80));
            aPayload[2].mid = (u8)((u32)vTranslationCopy.z >> 8);
            aPayload[2].lo = (u8)vTranslationCopy.z;

            actor->pNodeSlots[2].pResult =
                func_ov107_020c08cc(actor->taskList, actor->pNodeSlots[2].pSubitem,
                                    5, 0, 0x999, aPayload);
            break;
        }
    }
    func_ov107_020c7500(actor, msg, param);
}
