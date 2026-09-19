/* Message handler of the ov125 enemy. A "spawned" message (kind 5) is dispatched on its
 * sub-kind: 0 starts the +0x39c set's entry 0 (mode 5, weight 0x1000, the packet's payload)
 * into entry 1; 1 activates the aim node and registers effect 0x11b (kind 7) on the +0xa0 node
 * into +0x3a8; 2 deactivates the aim node; 3 starts entries 0xc and 0xe (mode 0x15, weight
 * 0x800) into 0xd / 0xf with the +0x394 / +0x398 anchors' +0x14 positions packed as the
 * payload; 4 restarts whichever of those two is idle (entry 0xd checked first) at weight
 * 0x1000 with the packet's payload; 5 registers effect 0x11b (kind 5, flag 1) into +0x3ac. The
 * base handler always runs.
 *
 * Codegen: the packed positions go through Fx32 wrapper copies (ov122_020d12f4 idiom) -- the
 * unread word stores at the frame bottom are the ROM's. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;

extern void *func_ov107_020c08cc(void *taskList, void *subitem, int mode, int blend, int weight, void *payload);
extern int func_0203c6e0(void *taskList, void *subitem);
extern void func_ov126_020d219c(int node, int active);
extern int func_ov107_020cb040(int owner, int resourceId, int kind, int flag, void *work);
extern void func_ov107_020c7500(int actor, unsigned char *msg, int param);

void func_ov126_020cffc4(int actor, unsigned char *msg, int param)
{
    u8 payload[9];
    FxVec vA;
    FxVec vB;
    char *anchor;

    if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
            (*(void ***)(actor + 0x39c))[1] =
                func_ov107_020c08cc(*(void **)(actor + 0x3c), (*(void ***)(actor + 0x39c))[0], 5, 0, 0x1000, msg + 5);
            break;
        case 4:
            if (func_0203c6e0(*(void **)(actor + 0x3c), (*(void ***)(actor + 0x39c))[0xd]) == 0) {
                (*(void ***)(actor + 0x39c))[0xd] =
                    func_ov107_020c08cc(*(void **)(actor + 0x3c), (*(void ***)(actor + 0x39c))[0xc], 0x15, 0, 0x1000, msg + 5);
            } else {
                (*(void ***)(actor + 0x39c))[0xf] =
                    func_ov107_020c08cc(*(void **)(actor + 0x3c), (*(void ***)(actor + 0x39c))[0xe], 0x15, 0, 0x1000, msg + 5);
            }
            break;
        case 1:
            func_ov126_020d219c(*(int *)(actor + 0x390), 1);
            *(int *)(actor + 0x3a8) = func_ov107_020cb040(actor, 0x11b, 7, 0, (void *)(actor + 0xa0));
            break;
        case 2:
            func_ov126_020d219c(*(int *)(actor + 0x390), 0);
            break;
        case 3:
            anchor = *(char **)(actor + 0x394);
            vA.x = *(Fx32 *)(anchor + 0x14);
            payload[0] = (u8)(((u32)vA.x.value >> 0x10 & 0x7f) | ((u32)vA.x.value >> 0x18 & 0x80));
            payload[1] = (u8)((u32)vA.x.value >> 8);
            payload[2] = (u8)vA.x.value;
            vA.y = *(Fx32 *)(anchor + 0x18);
            payload[3] = (u8)(((u32)vA.y.value >> 0x10 & 0x7f) | ((u32)vA.y.value >> 0x18 & 0x80));
            payload[4] = (u8)((u32)vA.y.value >> 8);
            payload[5] = (u8)vA.y.value;
            vA.z = *(Fx32 *)(anchor + 0x1c);
            payload[6] = (u8)(((u32)vA.z.value >> 0x10 & 0x7f) | ((u32)vA.z.value >> 0x18 & 0x80));
            payload[7] = (u8)((u32)vA.z.value >> 8);
            payload[8] = (u8)vA.z.value;
            (*(void ***)(actor + 0x39c))[0xd] =
                func_ov107_020c08cc(*(void **)(actor + 0x3c), (*(void ***)(actor + 0x39c))[0xc], 0x15, 0, 0x800, payload);
            anchor = *(char **)(actor + 0x398);
            vB.x = *(Fx32 *)(anchor + 0x14);
            payload[0] = (u8)(((u32)vB.x.value >> 0x10 & 0x7f) | ((u32)vB.x.value >> 0x18 & 0x80));
            payload[1] = (u8)((u32)vB.x.value >> 8);
            payload[2] = (u8)vB.x.value;
            vB.y = *(Fx32 *)(anchor + 0x18);
            payload[3] = (u8)(((u32)vB.y.value >> 0x10 & 0x7f) | ((u32)vB.y.value >> 0x18 & 0x80));
            payload[4] = (u8)((u32)vB.y.value >> 8);
            payload[5] = (u8)vB.y.value;
            vB.z = *(Fx32 *)(anchor + 0x1c);
            payload[6] = (u8)(((u32)vB.z.value >> 0x10 & 0x7f) | ((u32)vB.z.value >> 0x18 & 0x80));
            payload[7] = (u8)((u32)vB.z.value >> 8);
            payload[8] = (u8)vB.z.value;
            (*(void ***)(actor + 0x39c))[0xf] =
                func_ov107_020c08cc(*(void **)(actor + 0x3c), (*(void ***)(actor + 0x39c))[0xe], 0x15, 0, 0x800, payload);
            break;
        case 5:
            *(int *)(actor + 0x3ac) = func_ov107_020cb040(actor, 0x11b, 5, 1, (void *)(actor + 0xa0));
            break;
        }
    }
    func_ov107_020c7500(actor, msg, param);
}
