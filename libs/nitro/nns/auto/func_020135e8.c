typedef unsigned short u16;

#define NNS_G2D_GLYPH_INDEX_NOT_FOUND 0xffff

typedef enum NNSG2dFontMappingMethod {
    NNS_G2D_MAPMETHOD_DIRECT,
    NNS_G2D_MAPMETHOD_TABLE,
    NNS_G2D_MAPMETHOD_SCAN
} NNSG2dFontMappingMethod;

typedef struct NNSG2dFontCodeMap {
    u16 ccodeBegin;
    u16 ccodeEnd;
    u16 mappingMethod;
    u16 reserved;
    struct NNSG2dFontCodeMap *pNext;
    u16 mapInfo[1];
} NNSG2dFontCodeMap;

typedef struct NNSG2dCMapScanEntry {
    u16 ccode;
    u16 index;
} NNSG2dCMapScanEntry;

typedef struct NNSG2dCMapInfoScan {
    u16 num;
    NNSG2dCMapScanEntry entries[1];
} NNSG2dCMapInfoScan;

u16 func_020135e8(const NNSG2dFontCodeMap *pMap, u16 c)
{
    u16 index = NNS_G2D_GLYPH_INDEX_NOT_FOUND;

    switch (pMap->mappingMethod) {
    case NNS_G2D_MAPMETHOD_DIRECT:
    {
        u16 offset = pMap->mapInfo[0];
        index = (u16)(c - pMap->ccodeBegin + offset);
    }
    break;
    case NNS_G2D_MAPMETHOD_TABLE:
    {
        const int table_index = c - pMap->ccodeBegin;

        index = pMap->mapInfo[table_index];
    }
    break;
    case NNS_G2D_MAPMETHOD_SCAN:
    {
        const NNSG2dCMapInfoScan * const ws =
            (NNSG2dCMapInfoScan *)pMap->mapInfo;
        const NNSG2dCMapScanEntry *st = &ws->entries[0];
        const NNSG2dCMapScanEntry *ed = &ws->entries[ws->num - 1];

        while (st <= ed) {
            const NNSG2dCMapScanEntry *md = st + (ed - st) / 2;

            if (md->ccode < c) {
                st = md + 1;
            } else if (c < md->ccode) {
                ed = md - 1;
            } else {
                index = md->index;
                break;
            }
        }
    }
    break;
    default:
        break;
    }

    return index;
}
