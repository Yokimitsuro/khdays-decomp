/* NOT MATCHING -- 456 of 460 bytes.  The ROM keeps the inner entry counter in r7 and
 * spills the compiler's row cursor (&spec + 8 * i, the +4 / +5 / +8 folded) at [sp]; build
 * 139 keeps the cursor in r7 and spills the counter for every form tried (declaration
 * orders, explicit row / spec pointers, entries indexed by the running total or from the
 * row base, per-row entry pointers, address-taken or volatile counters, C99 / block /
 * register / narrow counters, earlier counter initialisation, while / do / goto forms, no
 * guard, prototypes, pragmas).  Everything else now matches: the never-read entry counter
 * and the case-2 key live in a small struct declared after the entry array (sp+0x10 /
 * sp+0x14 like the ROM), and the entries are indexed by a plain running index so the entry
 * cursor is the loop optimiser's induction (initialised in the preheader).  Notes: build/held. */
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
    struct {
        volatile int nTotal;
        int nKey;
    } g;
    int nBase;
    int nTarget;
    int nSlot;
    int i;
    int j;
    int nArg;
    u16 *pOperand;

    g.nTotal = 0;
    nTarget = func_02021980(vm, pc);
    nSlot = func_02021980(vm, pc + 4);
    pOperand = pc + 8;
    pc += 0xc;
    spec.nRows = func_02021980(vm, pOperand);
    nBase = 0;
    for (i = 0; i < spec.nRows; i++) {
        spec.aRow[i].nTable = func_02021980(vm, pc);
        pOperand = pc + 4;
        pc += 8;
        spec.aRow[i].nCount = func_02021980(vm, pOperand);
        spec.aRow[i].aEntry = &aEntry[nBase];
        if (spec.aRow[i].nCount > 0) {
            for (j = 0; j < spec.aRow[i].nCount; j++) {
                aEntry[nBase].nId = func_02021980(vm, pc);
                aEntry[nBase].nKey = func_02021980(vm, pc + 4);
                aEntry[nBase].nKind = func_02021980(vm, pc + 8);
                aEntry[nBase].aLink[0] = func_02021980(vm, pc + 0xc);
                aEntry[nBase].aLink[1] = func_02021980(vm, pc + 0x10);
                aEntry[nBase].aLink[2] = func_02021980(vm, pc + 0x14);
                pOperand = pc + 0x18;
                pc += 0x1c;
                aEntry[nBase].aLink[3] = func_02021980(vm, pOperand);
                switch (aEntry[nBase].nKind) {
                case 0:
                    aEntry[nBase].u.position.x = func_02021994(vm, pc);
                    aEntry[nBase].u.position.y = func_02021994(vm, pc + 4);
                    pOperand = pc + 8;
                    pc += 0xc;
                    aEntry[nBase].u.position.z = func_02021994(vm, pOperand);
                    break;
                case 1:
                    aEntry[nBase].u.position.x = func_02021994(vm, pc);
                    aEntry[nBase].u.position.y = func_02021994(vm, pc + 4);
                    aEntry[nBase].u.position.z = func_02021994(vm, pc + 8);
                    aEntry[nBase].nLinkTable = func_02021980(vm, pc + 0xc);
                    pOperand = pc + 0x10;
                    pc += 0x14;
                    aEntry[nBase].nLinkId = func_02021980(vm, pOperand);
                    break;
                case 2:
                    g.nKey = func_02021980(vm, pc);
                    pOperand = pc + 4;
                    pc += 8;
                    nArg = func_02021980(vm, pOperand);
                    aEntry[nBase].u.pPickup = func_ov002_0207679c(g.nKey, nArg);
                    break;
                }
                g.nTotal++;
                nBase++;
            }
        }
    }
    func_ov002_0207643c(nTarget, func_ov015_02080df8(nSlot, &spec));
    return 1;
}
