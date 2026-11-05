/* Ov016_ScriptOpCreateFollower -- Ov016_ScriptOpCreateFollower: script op that reads a slot, a kind and
 * an index, a packed GameState field / bit word (pc + 0x1c), the player to trail, the range
 * (fx32), the hold time in seconds (fx32), the turn rate and -- when the operand at pc + 0x40
 * is present -- the cone in degrees (turned into a 16-bit angle by degrees * 0x10000 / 360;
 * 90 by default), then creates a follower piece (Ov016_FollowerCreate 02080810) on the slot's
 * class table (ov002 02076468).  Always consumes the op (1). */

#include "nitro/types.h"

extern int   ScriptVm_ReadOperandInt(int vm, u16 *pc);            /* ScriptVm_ReadOperandInt */
extern int   ScriptVm_ReadOperandFx32(int vm, u16 *pc);            /* ScriptVm_ReadOperandFx32 */
extern long long func_02020400(int nNumerator, int nDenominator); /* _s32_div_f */
extern void *Ov002_GetModuleSlot(int nSlot);            /* class table of a slot */
extern void *Ov016_FollowerCreate(void *pClass, u16 nSlot, u16 nRoom, u16 nField, u8 nBit,
                                 int nPlayer, int nRange, int nSeconds, int nTurnRate, int nCone); /* Ov016_FollowerCreate */

int Ov016_ScriptOpCreateFollower(int vm, u16 *pc)
{
    u16 nField;
    u8 nBit;
    int nSlot;
    u32 nKind;
    u32 nIndex;
    u32 nRaw;
    int nPlayer;
    int nRange;
    int nSeconds;
    int nTurnRate;
    u32 nCone;
    void *pClass;

    nSlot = ScriptVm_ReadOperandInt(vm, pc);
    nKind = ScriptVm_ReadOperandInt(vm, pc + 4);
    nIndex = ScriptVm_ReadOperandInt(vm, pc + 8);
    nRaw = *(u32 *)(pc + 0xe);
    nField = nRaw;
    nBit = (u16)(nRaw >> 16);
    nPlayer = ScriptVm_ReadOperandInt(vm, pc + 0x10);
    nRange = ScriptVm_ReadOperandFx32(vm, pc + 0x14);
    nSeconds = ScriptVm_ReadOperandFx32(vm, pc + 0x18);
    nTurnRate = ScriptVm_ReadOperandInt(vm, pc + 0x1c);
    nCone = 90;
    if (((short *)pc)[0x20] != 0) {
        nCone = (u16)func_02020400(ScriptVm_ReadOperandInt(vm, pc + 0x20) << 16, 360);
    }
    pClass = Ov002_GetModuleSlot(nSlot);
    Ov016_FollowerCreate(pClass, nKind & 0xffff, nIndex & 0xffff, nField, nBit, nPlayer, nRange, nSeconds, nTurnRate, nCone);
    return 1;
}
