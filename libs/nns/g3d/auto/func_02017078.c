typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000

#define offsetof(type, member) ((u32)&(((type *)0)->member))



typedef struct NNSG3dResFileHeader_ {
    union {
        char signature[4];
        u32 sigVal;
    };
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 dataBlocks;
} NNSG3dResFileHeader;
typedef struct NNSG3dResDataBlockHeader_ {
    union {
        u32 kind;
        char chr[4];
    };
    u32 size;
} NNSG3dResDataBlockHeader;
typedef struct NNSG3dResDictTreeNode_ {
    u8 refBit;
    u8 idxLeft;
    u8 idxRight;
    u8 idxEntry;
} NNSG3dResDictTreeNode;
typedef struct NNSG3dResDict_ {
    u8 revision;
    u8 numEntry;
    u16 sizeDictBlk;
    u16 dummy_;
    u16 ofsEntry;
    NNSG3dResDictTreeNode node[1];
} NNSG3dResDict;
typedef struct NNSG3dResMdlSet_ {
    NNSG3dResDataBlockHeader header;
    NNSG3dResDict dict;
} NNSG3dResMdlSet;

/* func_02017078 -- NitroSystem res_struct_accessor.c: NNS_G3dGetMdlSet. */
NNSG3dResMdlSet * func_02017078 (const NNSG3dResFileHeader * header)
{
    u32 * blks;

    blks = (u32 *)((u8 *)header + header->headerSize);
    return (NNSG3dResMdlSet *)((u8 *)header + blks[0]);
}
