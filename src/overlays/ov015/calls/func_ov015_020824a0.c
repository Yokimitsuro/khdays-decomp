/* func_ov015_020824a0 -- Ov015_ScriptOpSpawnTrigger: script op that reads a slot, a kind,
 * an index, the raw word at pc + 0x1c (low half the GameState field, next byte its bit),
 * a parameter word, the centre (three fx32), a shape, the extent (three fx32) and the
 * name (a resolved operand), then spawns a trigger piece (0208061c) on the slot's class
 * table (ov002 02076468).  Always consumes the op (1). */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

extern int   func_02021980(int vm, u16 *pc);            /* ScriptVm_ReadOperandInt */
extern int   func_02021994(int vm, u16 *pc);            /* ScriptVm_ReadOperandFx32 */
extern void *func_02021948(int vm, u16 *pc);            /* ByteCode_ResolveOperand */
extern void *func_ov002_02076468(int nSlot);            /* class table of a slot */
extern void *func_ov015_0208061c(void *pClass, int nSlot, int nKind, int nField, u8 nBit, VecFx32 *pCentre, int nParam, s8 nShape, VecFx32 *pExtent, const char *pName);

int func_ov015_020824a0(int vm, u16 *pc)
{
    VecFx32 centre;
    VecFx32 extent;
    int nSlot;
    u32 nKind;
    u32 nIndex;
    u32 nFieldBit;
    int nParam;
    u32 nShape;
    const char *pName;
    u16 nBitHalf;

    nSlot = func_02021980(vm, pc);
    nKind = func_02021980(vm, pc + 4);
    nIndex = func_02021980(vm, pc + 8);
    nFieldBit = *(u32 *)(pc + 0xe);
    nParam = func_02021980(vm, pc + 0x10);
    centre.x = func_02021994(vm, pc + 0x14);
    centre.y = func_02021994(vm, pc + 0x18);
    centre.z = func_02021994(vm, pc + 0x1c);
    nShape = func_02021980(vm, pc + 0x20);
    extent.x = func_02021994(vm, pc + 0x24);
    extent.y = func_02021994(vm, pc + 0x28);
    extent.z = func_02021994(vm, pc + 0x2c);
    pName = func_02021948(vm, pc + 0x30);
    nBitHalf = nFieldBit >> 16;
    func_ov015_0208061c(func_ov002_02076468(nSlot), nKind & 0xffff, nIndex & 0xffff, nFieldBit & 0xffff, nBitHalf, &centre, nParam, (s8)nShape, &extent, pName);
    return 1;
}
