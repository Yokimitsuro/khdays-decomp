/* Ov011_CreateTitleObjects -- build the two object managers of the title
 * scene (+0x23ad0 and +0x28508) from the scene's archive base (VRAM address
 * word: (base + 0x8000) & 0xfffffc, << 7, flags 0x80000008; kinds 1 and 2),
 * allocate objects 0..3 from each into the two handle tables (+0x1091c and
 * +0x2125c), then a fifth object (index 4) from the second manager whose
 * handle is kept at +0x2cf40 and cleared of flag bit 1.
 */

typedef unsigned char u8;
typedef unsigned int u32;

/* ObjNodeDesc */
struct ObjDesc {
    u32 nAddress;                /* 0x00 */
    int nKind;                   /* 0x04 */
    int nReserved0;              /* 0x08 */
    int nReserved1;              /* 0x0c */
};

/* Ov011Scene */
struct Scene {
    u8 pad00000[0xc];
    u32 nArchiveBase;            /* 0x0000c */
    u8 pad00010[0x1090c];
    int aHandleA[4];             /* 0x1091c */
    u8 pad1092c[0x10930];
    int aHandleB[4];             /* 0x2125c */
    u8 pad2126c[0x2864];
    u8 managerA[0x4a38];         /* 0x23ad0 */
    u8 managerB[0x4a38];         /* 0x28508 */
    int nCursorHandle;           /* 0x2cf40 */
};

#define VRAM_BASE_MASK 0xfffffc
#define VRAM_BASE_ROUND 0x8000
#define DESC_FLAGS 0x80000008
#define OBJECT_COUNT 4
#define CURSOR_INDEX 4

/* khdays: shared-bss */
int data_ov011_0205e960 = 0;                                                  /* gOv011Cursor */
struct Scene *data_ov011_0205e964 = 0;                                         /* gpOv011Scene */

extern void func_02032388(void *pManager, struct ObjDesc *pDesc);              /* ObjNode_InitFromDesc */
extern int func_ov011_0205d664(void *pManager, int nIndex);                     /* ov011_AllocAndRegisterObject */
extern void func_020326cc(void *pManager, int nObject);                         /* Slot_ClearFlagBit1 */

void func_ov011_0205d6a0(void)
{
    struct ObjDesc desc;
    int i;

    desc.nAddress = ((data_ov011_0205e964->nArchiveBase + VRAM_BASE_ROUND & VRAM_BASE_MASK) << 7) | DESC_FLAGS;
    desc.nKind = 1;
    desc.nReserved0 = 0;
    desc.nReserved1 = 0;
    func_02032388(data_ov011_0205e964->managerA, &desc);
    desc.nKind = 2;
    func_02032388(data_ov011_0205e964->managerB, &desc);
    for (i = 0; i < OBJECT_COUNT; i++) {
        data_ov011_0205e964->aHandleA[i] = func_ov011_0205d664(data_ov011_0205e964->managerA, i);
        data_ov011_0205e964->aHandleB[i] = func_ov011_0205d664(data_ov011_0205e964->managerB, i);
    }
    data_ov011_0205e964->nCursorHandle = func_ov011_0205d664(data_ov011_0205e964->managerB, CURSOR_INDEX);
    func_020326cc(data_ov011_0205e964->managerB, data_ov011_0205e964->nCursorHandle);
}
