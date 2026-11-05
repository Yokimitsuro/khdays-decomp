/*
 * Game_ActionLoadArenaResource - action-command handler dispatched from the opcode table
 * data_020425ec (see Game_RunActionScript / Game_RunActionScript). Resolves up to two bytecode
 * operands from the command stream: a path string (cmd[0]) and an optional operand (cmd[4]).
 *
 *  - No path: append the entry's slot with the operand (Game_PushObjectSlot) and return 2.
 *  - Path "3:..." : resolve the filename (Ov023_BuildEventTextPath), copy it, open the message
 *    container (Msg_OpenContainerAndReadHeader), load it into the arena at state+0x594 through FileLoader_LoadInto
 *    (destination encoded as an aligned address | 0x80000000), free the header, and raise the
 *    game-state flag GameState_SetField(0x2484, 1, 0).
 *  - Path "N:..." : look up a resource slot at *(state[0x4a] + idx*4 + 0x48c) and load it into
 *    the same arena.
 *
 * FileLoader_LoadInto returns the number of bytes consumed (<0 on failure -> return 0). The size is
 * rounded up to a multiple of 4 and written into the next entry (entries[count+1] + 8), then
 * Slot48_StoreAtCurrentIndex records the command. avail = *(state+0x590) - state[0] is the arena
 * space remaining; the destination is state+0x594 + state[0] (a bump cursor).
 *
 * THUMB. Matching notes: FileLoader_LoadInto is declared prototypeless because it is used variadically -
 * the "3:" branch passes 3 arguments (leaving r3 scratch) while the "N:" branch passes 4 (r3 = the
 * encoded VRAM base, shared with argument 1). The command stream is signed s16 (ldrsh). The entry
 * stride is 0x48 and the arena offset 0x594 is kept in one register so 0x590 is derived as 0x594-4.
 */

#include "nitro/types.h"
#include "game/archive.h"

extern int   ByteCode_ResolveOperand(int st, short *cmd);
extern void  Game_PushObjectSlot(int *st, int *slot, int a, u32 *operand);
extern char *Ov023_BuildEventTextPath(char *s);
extern void  strcpy(void *dst, void *src);
extern u32  *Msg_OpenContainerAndReadHeader(void *buf, int n);
extern int   FileLoader_LoadInto();
extern void  ZeroHalfThenFree(void *p);
extern void  GameState_SetField(int a, int b, int c);
extern int   func_020200b4(char *s);
extern u32   MsgArchive_FindEntryByName(int a, char *s);
extern void  Slot48_StoreAtCurrentIndex(int *st, short *cmd);
extern int   data_0204bdbc;

int Game_ActionLoadArenaResource(int *param_1, short *param_2)
{
    char *dst_base = (char *)param_1 + 0x594;
    int   owner = param_1[0];
    u32   avail = *(int *)((char *)param_1 + 0x590) - owner;
    char *path;
    u32  *operand;
    int   i5;
    int   result;

    i5 = param_2[0];
    path = 0;
    if (i5 != 0) path = (char *)ByteCode_ResolveOperand((int)param_1, param_2);
    if (param_2[4] != 0) operand = (u32 *)ByteCode_ResolveOperand((int)param_1, param_2 + 4);
    else operand = 0;

    if (path == 0) {
        Game_PushObjectSlot(param_1,
                      *(int **)((char *)param_1 + param_1[0x49] * 0x48 + 4),
                      0, operand);
        return 2;
    }
    if (path[1] == ':') {
        if (path[0] == '3') {
            u32 *hdr;
            u32  flags;
            char tmp[0x20];
            hdr = (u32 *)Ov023_BuildEventTextPath(path);
            strcpy(tmp, hdr);
            hdr = Msg_OpenContainerAndReadHeader(tmp, 0xf);
            flags = (((u32)(hdr + 0x2000) & 0xfffffc) << 7) | 0x80000000
                    | ((0xfffffc >> 0xf) & *(u32 *)((char *)&data_0204bdbc + 0x40));
            result = FileLoader_LoadInto((char *)flags, (int)dst_base + owner, avail);
            ZeroHalfThenFree(hdr);
            GameState_SetField(0x2484, 1, 0);
        } else {
            int slot;
            u32 v;
            u32 uVar6;
            slot = *(int *)(param_1[0x4a] + func_020200b4(path) * 4 + 0x48c);
            if (path[0] == '0') v = MsgArchive_FindEntryByName(slot, path + 2);
            else v = func_020200b4(path + 2);
            uVar6 = ARCHIVE_HANDLE(slot, 0);
            result = FileLoader_LoadInto((char *)((v & (0xfffffc >> 0xf)) | uVar6),
                                   (int)dst_base + owner, avail, uVar6);
        }
    }
    if (result < 0) return 0;
    { int m = result % 4; if (m != 0) result += 4 - m; }
    *(int *)((char *)param_1 + (param_1[0x49] + 1) * 0x48 + 8) = result;
    Slot48_StoreAtCurrentIndex(param_1, param_2);
    return 0;
}
