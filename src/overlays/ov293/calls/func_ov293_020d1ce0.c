/* Message handler of the ov293 enemy: a "spawned" message (kind 5) starts the first +0x3a0
 * node slot's subitem (sub-kind 0, mode 5, weight 0x999) with the packet's payload bytes, or
 * the second slot's (sub-kind 1) with the actor's own +0xb0 position packed as three big-endian
 * 24-bit values; the base handler always runs. Coordinates are copied through the Fx32 wrapper
 * (the ROM's unread stack copy of the position), as in ov122_020d12f4. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;

struct Ov293Node {
    char pad000[0x3c];
    void *pTaskList;            /* +0x3c */
    char pad040[0xb0 - 0x40];
    FxVec vPos;                 /* +0xb0 */
    char pad0bc[0x3a0 - 0xbc];
    void **pSlots;              /* +0x3a0 */
};

extern void *func_ov107_020c08cc(void *taskList, void *subitem, int mode, int blend, int weight, void *payload);
extern void func_ov107_020c7500(struct Ov293Node *actor, unsigned char *msg, int param);

void func_ov293_020d1ce0(struct Ov293Node *actor, unsigned char *msg, int param)
{
    u8 packed[9];
    FxVec v;

    if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
            actor->pSlots[1] = func_ov107_020c08cc(actor->pTaskList, actor->pSlots[0], 5, 0, 0x999, msg + 5);
            break;
        case 1:
            v.x = actor->vPos.x;
            packed[0] = (u8)(((u32)v.x.value >> 0x10 & 0x7f) | ((u32)v.x.value >> 0x18 & 0x80));
            packed[2] = (u8)v.x.value;
            packed[1] = (u8)((u32)v.x.value >> 8);
            v.y = actor->vPos.y;
            packed[3] = (u8)(((u32)v.y.value >> 0x10 & 0x7f) | ((u32)v.y.value >> 0x18 & 0x80));
            packed[5] = (u8)v.y.value;
            packed[4] = (u8)((u32)v.y.value >> 8);
            v.z = actor->vPos.z;
            packed[6] = (u8)(((u32)v.z.value >> 0x10 & 0x7f) | ((u32)v.z.value >> 0x18 & 0x80));
            packed[8] = (u8)v.z.value;
            packed[7] = (u8)((u32)v.z.value >> 8);
            actor->pSlots[3] = func_ov107_020c08cc(actor->pTaskList, actor->pSlots[2], 5, 0, 0x999, packed);
            break;
        }
    }
    func_ov107_020c7500(actor, msg, param);
}
