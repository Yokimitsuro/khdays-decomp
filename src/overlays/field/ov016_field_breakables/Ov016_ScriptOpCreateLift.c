/* Ov016_ScriptOpCreateLift -- Ov016_ScriptOpCreateLift: script op that reads a slot, a kind and an
 * index, two packed GameState field / bit words (pc + 0x1c: the lift's own state, pc + 0x24:
 * the trigger), the position (three fx32), an angle in degrees (turned into a 16-bit facing
 * by angle * 0x10000 / 360), the top and bottom heights, the speed and -- when the operand at
 * pc + 0x60 is present -- the wait in seconds (times 30 frames; 60 seconds by default),
 * then creates a lift piece (Ov016_LiftCreate 0207ff40) on the slot's class table (ov002
 * 02076468).  Always consumes the op (1). */

#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int   ScriptVm_ReadOperandInt(int vm, u16 *pc);            /* ScriptVm_ReadOperandInt */
extern int   ScriptVm_ReadOperandFx32(int vm, u16 *pc);            /* ScriptVm_ReadOperandFx32 */
extern long long func_02020400(int nNumerator, int nDenominator); /* _s32_div_f */
extern void *Ov002_GetModuleSlot(int nSlot);            /* class table of a slot */
extern void *Ov016_LiftCreate(void *pClass, u16 nSlot, u16 nRoom, VecFx32 *pPos, short nFacing,
                                 u16 nField, u8 nBit, u16 nTriggerField, u8 nTriggerBit,
                                 int nTop, int nBottom, int nSpeed, int nWait);   /* Ov016_LiftCreate */

int Ov016_ScriptOpCreateLift(int vm, u16 *pc)
{
    VecFx32 position;
    u16 nField;
    u8 nBit;
    u16 nFacing;
    u16 nTriggerField;
    u8 nTriggerBit;
    int nSlot;
    u32 nKind;
    u32 nIndex;
    u32 nRaw;
    int nTop;
    int nBottom;
    int nSpeed;
    int nWait;
    void *pClass;

    nSlot = ScriptVm_ReadOperandInt(vm, pc);
    nKind = ScriptVm_ReadOperandInt(vm, pc + 4);
    nIndex = ScriptVm_ReadOperandInt(vm, pc + 8);
    nRaw = *(u32 *)(pc + 0xe);
    nField = nRaw;
    nBit = (u16)(nRaw >> 16);
    nRaw = *(u32 *)(pc + 0x12);
    nTriggerField = nRaw;
    nTriggerBit = (u16)(nRaw >> 16);
    position.x = ScriptVm_ReadOperandFx32(vm, pc + 0x14);
    position.y = ScriptVm_ReadOperandFx32(vm, pc + 0x18);
    position.z = ScriptVm_ReadOperandFx32(vm, pc + 0x1c);
    nFacing = (u16)func_02020400(ScriptVm_ReadOperandInt(vm, pc + 0x20) << 16, 360);
    nTop = ScriptVm_ReadOperandFx32(vm, pc + 0x24);
    nBottom = ScriptVm_ReadOperandFx32(vm, pc + 0x28);
    nSpeed = ScriptVm_ReadOperandFx32(vm, pc + 0x2c);
    nWait = 0x3c000;
    if (((short *)pc)[0x30] != 0) {
        nWait = ScriptVm_ReadOperandFx32(vm, pc + 0x30) * 30;
    }
    pClass = Ov002_GetModuleSlot(nSlot);
    Ov016_LiftCreate(pClass, nKind & 0xffff, nIndex & 0xffff, &position, nFacing, nField, nBit,
                        nTriggerField, nTriggerBit, nTop, nBottom, nSpeed, nWait);
    return 1;
}
