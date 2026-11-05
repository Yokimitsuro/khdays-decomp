/* Ov016_ScriptOpCreateHazard -- Ov016_ScriptOpCreateHazard: script op that reads the position (three
 * fx32 at pc + 0x20), a packed GameState field / bit word (pc + 0x1c, kept whole and split at
 * the call) and an angle in degrees (facing = angle * 0x10000 / 360), then the slot's class
 * table (ov002 02076468 on the first operand), the kind and the index, and creates a hazard
 * piece (Ov016_HazardCreate 02082664).  Always consumes the op (1). */

#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int   ScriptVm_ReadOperandInt(int vm, u16 *pc);            /* ScriptVm_ReadOperandInt */
extern int   ScriptVm_ReadOperandFx32(int vm, u16 *pc);            /* ScriptVm_ReadOperandFx32 */
extern long long func_02020400(int nNumerator, int nDenominator); /* _s32_div_f */
extern void *Ov002_GetModuleSlot(int nSlot);            /* class table of a slot */
extern void *Ov016_HazardCreate(void *pClass, u16 nSlot, u16 nRoom, u16 nField, u8 nBit, VecFx32 *pPos, short nFacing); /* Ov016_HazardCreate */

int Ov016_ScriptOpCreateHazard(int vm, u16 *pc)
{
    VecFx32 position;
    u32 nKind;
    u32 nIndex;
    void *pClass;
    u32 nRaw;
    u16 nFacing;

    position.x = ScriptVm_ReadOperandFx32(vm, pc + 0x10);
    position.y = ScriptVm_ReadOperandFx32(vm, pc + 0x14);
    position.z = ScriptVm_ReadOperandFx32(vm, pc + 0x18);
    nRaw = *(u32 *)(pc + 0xe);
    nFacing = (u16)func_02020400(ScriptVm_ReadOperandInt(vm, pc + 0x1c) << 16, 360);
    pClass = Ov002_GetModuleSlot(ScriptVm_ReadOperandInt(vm, pc));
    nKind = ScriptVm_ReadOperandInt(vm, pc + 4);
    pc += 8;
    nIndex = ScriptVm_ReadOperandInt(vm, pc);
    Ov016_HazardCreate(pClass, nKind & 0xffff, nIndex & 0xffff, (u16)nRaw, (u16)(nRaw >> 16), &position, (short)nFacing);
    return 1;
}
