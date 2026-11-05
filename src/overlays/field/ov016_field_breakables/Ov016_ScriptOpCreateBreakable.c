/* Ov016_ScriptOpCreateBreakable -- Ov016_ScriptOpCreateBreakable: script op that reads a slot, a kind and
 * an index, a packed GameState field / bit word (pc + 0x1c), the position (three fx32), an
 * angle in degrees (turned into a 16-bit facing by angle * 0x10000 / 360) and the drop key
 * and argument, then creates a breakable piece (Ov016_BreakableCreate 02080ec0) on the
 * slot's class table (ov002 02076468).  Always consumes the op (1). */

#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int   ScriptVm_ReadOperandInt(int vm, u16 *pc);            /* ScriptVm_ReadOperandInt */
extern int   ScriptVm_ReadOperandFx32(int vm, u16 *pc);            /* ScriptVm_ReadOperandFx32 */
extern long long func_02020400(int nNumerator, int nDenominator); /* _s32_div_f */
extern void *Ov002_GetModuleSlot(int nSlot);            /* class table of a slot */
extern void *Ov016_BreakableCreate(void *pClass, u16 nSlot, u16 nRoom, VecFx32 *pPos, short nFacing,
                                 u16 nField, u8 nBit, int nDropKey, int nDropArg);   /* Ov016_BreakableCreate */

int Ov016_ScriptOpCreateBreakable(int vm, u16 *pc)
{
    VecFx32 position;
    int nSlot;
    u32 nKind;
    u32 nIndex;
    u32 nRaw;
    int nAngle;
    int nDropKey;
    int nDropArg;
    void *pClass;

    nSlot = ScriptVm_ReadOperandInt(vm, pc);
    nKind = ScriptVm_ReadOperandInt(vm, pc + 4);
    nIndex = ScriptVm_ReadOperandInt(vm, pc + 8);
    nRaw = *(u32 *)(pc + 0xe);
    position.x = ScriptVm_ReadOperandFx32(vm, pc + 0x10);
    position.y = ScriptVm_ReadOperandFx32(vm, pc + 0x14);
    position.z = ScriptVm_ReadOperandFx32(vm, pc + 0x18);
    nAngle = ScriptVm_ReadOperandInt(vm, pc + 0x1c);
    nDropKey = ScriptVm_ReadOperandInt(vm, pc + 0x20);
    pc += 0x24;
    nDropArg = ScriptVm_ReadOperandInt(vm, pc);
    pClass = Ov002_GetModuleSlot(nSlot);
    Ov016_BreakableCreate(pClass, nKind & 0xffff, nIndex & 0xffff, &position,
                        (short)func_02020400(nAngle << 16, 360), (u16)nRaw, (u16)(nRaw >> 16), nDropKey, nDropArg);
    return 1;
}
