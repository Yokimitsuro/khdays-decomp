/* NNS_G3dTexLoad-style upload of a TEX0 block through the installed VRAM loader
 * (data_0204bc08): the plain texel data goes to its vram key (<< 3) and the block is flagged
 * loaded; the 4x4-compressed texels follow at their key, their palette indices at the matching
 * GX_COMP4x4_PLTT_IDX address (half the size), and that part is flagged loaded too. */
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned char u8;

typedef struct {
    u32 vramKey;        /* 0x00 */
    u16 sizeTex;        /* 0x04 */
    u16 ofsDict;        /* 0x06 */
    u16 flag;           /* 0x08 */
    u16 dummy;          /* 0x0a */
    u32 ofsTex;         /* 0x0c */
} NNSG3dResTexInfo;

typedef struct {
    u32 vramKey;        /* 0x00 */
    u16 sizeTex;        /* 0x04 */
    u16 ofsDict;        /* 0x06 */
    u16 flag;           /* 0x08 */
    u16 dummy;          /* 0x0a */
    u32 ofsTex;         /* 0x0c */
    u32 ofsTexPlttIdx;  /* 0x10 */
} NNSG3dResTex4x4Info;

typedef struct {
    u32 header[2];
    NNSG3dResTexInfo texInfo;           /* 0x08 */
    NNSG3dResTex4x4Info tex4x4Info;     /* 0x18 */
} NNSG3dResTex;

extern void (*data_0204bc08)(const void *src, u32 dest, u32 size);

void func_02025364(NNSG3dResTex *pTex)
{
    u32 sz;
    u32 sz4;

    sz = (u32)pTex->texInfo.sizeTex << 3;
    if (sz != 0) {
        const void *pData = (u8 *)pTex + pTex->texInfo.ofsTex;
        u32 from = (pTex->texInfo.vramKey & 0xffff) << 3;

        data_0204bc08(pData, from, sz);
        pTex->texInfo.flag |= 1;
    }
    sz4 = (u32)pTex->tex4x4Info.sizeTex << 3;
    if (sz4 != 0) {
        const void *pData = (u8 *)pTex + pTex->tex4x4Info.ofsTex;
        const void *pDataPlttIdx = (u8 *)pTex + pTex->tex4x4Info.ofsTexPlttIdx;
        u32 from = (pTex->tex4x4Info.vramKey & 0xffff) << 3;

        data_0204bc08(pData, from, sz4);
        data_0204bc08(pDataPlttIdx, ((from & 0x1ffff) >> 1) + 0x20000 + ((from & 0x40000) >> 2), sz4 >> 1);
        pTex->tex4x4Info.flag |= 1;
    }
}
