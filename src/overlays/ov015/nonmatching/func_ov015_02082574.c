/* NOT MATCHING -- 456 of 460 bytes.  The ROM keeps the inner entry counter in r7 and
 * spills the compiler's row cursor (&spec + 8 * i, the +4 / +5 / +8 folded) at [sp]; build
 * 139 keeps the cursor in r7 and spills the counter for every form tried (declaration
 * orders, explicit row / spec pointers, entries indexed by the running total or from the
 * row base, per-row entry pointers, address-taken or volatile counters, C99 / block /
 * register / narrow counters, earlier counter initialisation, while forms, no guard,
 * prototypes).  Reusing the case-2 key temporary as the counter reproduces the ROM's spill
 * choice but then the key temporary loses its own slot.  The never-read entry counter at
 * [sp, #0x10] is reproduced with `volatile int nTotal`.  Notes: build/held. */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov015SpotEntry {
    s8  nId;                  /* 0x00 */
    s8  nKey;                 /* 0x01 */
    s8  nKind;                /* 0x02: 0 point, 1 link, 2 pickup */
    s8  aLink[4];             /* 0x03 */
    u8  pad_07;
    union {
        void *pPickup;        /* 0x08: pickup piece (kind 2) */
        VecFx32 position;     /* 0x08: point / link position */
    } u;
    s8  nLinkTable;           /* 0x14 */
    s8  nLinkId;              /* 0x15 */
    u8  pad_16[2];
} Ov015SpotEntry;

typedef struct Ov015SpotSpecRow {
    s8  nTable;               /* 0x00 */
    s8  nCount;               /* 0x01 */
    u8  pad_02[2];
    Ov015SpotEntry *aEntry;   /* 0x04 */
} Ov015SpotSpecRow;

typedef struct Ov015SpotSpec {
    s8  nRows;                /* 0x00 */
    u8  pad_01[3];
    Ov015SpotSpecRow aRow[9]; /* 0x04 */
} Ov015SpotSpec;

extern int   func_02021980(int vm, u16 *pc);            /* ScriptVm_ReadOperandInt */
extern int   func_02021994(int vm, u16 *pc);            /* ScriptVm_ReadOperandFx32 */
extern void *func_ov002_0207679c(u8 nKey, u16 nArg);    /* resolve a pickup piece */
extern void *func_ov015_02080df8(u16 nSlot, Ov015SpotSpec *pSpec); /* Ov015_CreateSpotClass */
extern void  func_ov002_0207643c(int nTarget, void *pValue);       /* store on the target */

int func_ov015_02082574(int vm, u16 *pc)
{
    Ov015SpotSpec spec;
    Ov015SpotEntry aEntry[128];
    Ov015SpotEntry *pEntry;
    int nTarget;
    int nSlot;
    volatile int nTotal;
    int i;
    int j;
    int nKey;
    int nArg;
    u16 *pOperand;

    nTotal = 0;
    nTarget = func_02021980(vm, pc);
    nSlot = func_02021980(vm, pc + 4);
    pOperand = pc + 8;
    pc += 0xc;
    spec.nRows = func_02021980(vm, pOperand);
    pEntry = aEntry;
    for (i = 0; i < spec.nRows; i++) {
        spec.aRow[i].nTable = func_02021980(vm, pc);
        pOperand = pc + 4;
        pc += 8;
        spec.aRow[i].nCount = func_02021980(vm, pOperand);
        spec.aRow[i].aEntry = pEntry;
        if (spec.aRow[i].nCount > 0) {
            for (j = 0; j < spec.aRow[i].nCount; j++) {
                pEntry->nId = func_02021980(vm, pc);
                pEntry->nKey = func_02021980(vm, pc + 4);
                pEntry->nKind = func_02021980(vm, pc + 8);
                pEntry->aLink[0] = func_02021980(vm, pc + 0xc);
                pEntry->aLink[1] = func_02021980(vm, pc + 0x10);
                pEntry->aLink[2] = func_02021980(vm, pc + 0x14);
                pOperand = pc + 0x18;
                pc += 0x1c;
                pEntry->aLink[3] = func_02021980(vm, pOperand);
                switch (pEntry->nKind) {
                case 0:
                    pEntry->u.position.x = func_02021994(vm, pc);
                    pEntry->u.position.y = func_02021994(vm, pc + 4);
                    pOperand = pc + 8;
                    pc += 0xc;
                    pEntry->u.position.z = func_02021994(vm, pOperand);
                    break;
                case 1:
                    pEntry->u.position.x = func_02021994(vm, pc);
                    pEntry->u.position.y = func_02021994(vm, pc + 4);
                    pEntry->u.position.z = func_02021994(vm, pc + 8);
                    pEntry->nLinkTable = func_02021980(vm, pc + 0xc);
                    pOperand = pc + 0x10;
                    pc += 0x14;
                    pEntry->nLinkId = func_02021980(vm, pOperand);
                    break;
                case 2:
                    nKey = func_02021980(vm, pc);
                    pOperand = pc + 4;
                    pc += 8;
                    nArg = func_02021980(vm, pOperand);
                    pEntry->u.pPickup = func_ov002_0207679c(nKey, nArg);
                    break;
                }
                nTotal++;
                pEntry++;
            }
        }
    }
    func_ov002_0207643c(nTarget, func_ov015_02080df8(nSlot, &spec));
    return 1;
}
