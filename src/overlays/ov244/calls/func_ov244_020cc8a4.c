/* Message handler of the ov244 enemy (x2 with ov277). A "spawned" message (kind 5) is dispatched on
 * its sub-kind through the +0x40c effect table: 0 starts the 020ce414 entry into slot 1, attaches
 * effects 0x13 / 0x17 at the +0x3cc bone into slots 3 / 5 and registers effect 0x113 (kind 0xa)
 * at the +0x3c8 bone into +0x490; 1 does the same with 020ce7d8 into slot 7, the attachments
 * flagged and effect 0x113 kind 4 into +0x494; 2 starts slot 0xe (mode 0x17, weight 1.0) into 0xf
 * with the packet's payload; 5 does it for slot 8 into 9 with the +0x3b0 prop's +0x14 position
 * packed as the payload; 3 clears bit 4 of +0x420 and starts 020cedb4 into slot 0xb; 4 sets that
 * bit; 6 registers effect 0x113 (kind 0xd) at the +0x3b0 prop into +0x498; 7 starts 020cf010 into
 * slot 0xd and 020cf490 into slot 7. The base handler always runs.
 *
 * Codegen: the packed position goes through Fx32 wrapper copies (ov125_020cc384 idiom). */
typedef unsigned char u8;
typedef unsigned int u32;
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;

extern int func_ov244_020ce414(char *self, int item);
extern int func_ov244_020ce7d8(char *self, int item);
extern int func_ov244_020cedb4(char *self, int item);
extern int func_ov244_020cf010(char *self, int item);
extern int func_ov244_020cf490(char *self, int item);
extern int func_ov107_020c09a0(int model, int parent, int kind, void *at, int a, int b);
extern int func_ov107_020c08cc(int taskList, int subitem, int mode, int blend, int weight, void *payload);
extern int func_ov107_020cb040(char *owner, int resourceId, int kind, int flag, void *work);
extern void func_ov107_020c7500(char *actor, unsigned char *msg, int param);

void func_ov244_020cc8a4(char *self, unsigned char *msg, int param)
{
    u8 payload[9];
    FxVec vAt;
    char *anchor;

    if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
            (*(int **)(self + 0x40c))[1] = func_ov244_020ce414(self, (*(int **)(self + 0x40c))[0]);
            (*(int **)(self + 0x40c))[3] = func_ov107_020c09a0(*(int *)(self + 0x3c), (*(int **)(self + 0x40c))[2], 0x13, (void *)(*(int *)(self + 0x3cc) + 4), 0, 0);
            (*(int **)(self + 0x40c))[5] = func_ov107_020c09a0(*(int *)(self + 0x3c), (*(int **)(self + 0x40c))[4], 0x17, (void *)(*(int *)(self + 0x3cc) + 4), 0, 0);
            *(int *)(self + 0x490) = func_ov107_020cb040(self, 0x113, 0xa, 0, (void *)(*(int *)(self + 0x3c8) + 4));
            break;
        case 1:
            (*(int **)(self + 0x40c))[7] = func_ov244_020ce7d8(self, (*(int **)(self + 0x40c))[6]);
            (*(int **)(self + 0x40c))[3] = func_ov107_020c09a0(*(int *)(self + 0x3c), (*(int **)(self + 0x40c))[2], 0x13, (void *)(*(int *)(self + 0x3cc) + 4), 1, 0);
            (*(int **)(self + 0x40c))[5] = func_ov107_020c09a0(*(int *)(self + 0x3c), (*(int **)(self + 0x40c))[4], 0x17, (void *)(*(int *)(self + 0x3cc) + 4), 1, 0);
            *(int *)(self + 0x494) = func_ov107_020cb040(self, 0x113, 4, 0, (void *)(*(int *)(self + 0x3c8) + 4));
            break;
        case 2:
            (*(int **)(self + 0x40c))[0xf] = func_ov107_020c08cc(*(int *)(self + 0x3c), (*(int **)(self + 0x40c))[0xe], 0x17, 0, 0x1000, msg + 5);
            break;
        case 5:
            anchor = *(char **)(self + 0x3b0);
            vAt.x = *(Fx32 *)(anchor + 0x14);
            payload[0] = (u8)(((u32)vAt.x.value >> 0x10 & 0x7f) | ((u32)vAt.x.value >> 0x18 & 0x80));
            payload[1] = (u8)((u32)vAt.x.value >> 8);
            payload[2] = (u8)vAt.x.value;
            vAt.y = *(Fx32 *)(anchor + 0x18);
            payload[3] = (u8)(((u32)vAt.y.value >> 0x10 & 0x7f) | ((u32)vAt.y.value >> 0x18 & 0x80));
            payload[4] = (u8)((u32)vAt.y.value >> 8);
            payload[5] = (u8)vAt.y.value;
            vAt.z = *(Fx32 *)(anchor + 0x1c);
            payload[6] = (u8)(((u32)vAt.z.value >> 0x10 & 0x7f) | ((u32)vAt.z.value >> 0x18 & 0x80));
            payload[7] = (u8)((u32)vAt.z.value >> 8);
            payload[8] = (u8)vAt.z.value;
            (*(int **)(self + 0x40c))[9] = func_ov107_020c08cc(*(int *)(self + 0x3c), (*(int **)(self + 0x40c))[8], 0x17, 0, 0x1000, payload);
            break;
        case 3:
            *(int *)(self + 0x420) &= ~0x10;
            (*(int **)(self + 0x40c))[0xb] = func_ov244_020cedb4(self, (*(int **)(self + 0x40c))[0xa]);
            break;
        case 4:
            *(int *)(self + 0x420) |= 0x10;
            break;
        case 6:
            *(int *)(self + 0x498) = func_ov107_020cb040(self, 0x113, 0xd, 0, (void *)(*(int *)(self + 0x3b0) + 4));
            break;
        case 7:
            (*(int **)(self + 0x40c))[0xd] = func_ov244_020cf010(self, (*(int **)(self + 0x40c))[0xc]);
            (*(int **)(self + 0x40c))[7] = func_ov244_020cf490(self, (*(int **)(self + 0x40c))[6]);
            break;
        }
    }
    func_ov107_020c7500(self, msg, param);
}
