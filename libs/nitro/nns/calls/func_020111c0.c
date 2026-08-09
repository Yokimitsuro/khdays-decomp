typedef unsigned long u32;
typedef int BOOL;

#define TRUE 1
#define FALSE 0

#define NNS_GFD_PLTTSIZE_MIN 8
#define NNS_GFD_PLTTSIZE_MAX 0x7fff8
#define NNS_GFD_4PLTT_MAX_ADDR 0x10000
#define NNS_GFD_ALLOC_ERROR_PLTTKEY 0
#define NNS_GFD_ALLOC_FROM_LOW 1

typedef u32 NNSGfdPlttKey;

typedef struct NNSGfdFrmPlttVramManager {
    u32 loAddr;
    u32 hiAddr;
    u32 szTotal;
} NNSGfdFrmPlttVramManager;

extern NNSGfdFrmPlttVramManager data_02047364;

static inline u32 NNSi_GfdGetPlttKeyRoundupSize(u32 size)
{
    if (size == 0) {
        return NNS_GFD_PLTTSIZE_MIN;
    } else {
        return (size + 7) & ~7;
    }
}

static inline NNSGfdPlttKey NNS_GfdMakePlttKey(u32 addr, u32 size)
{
    (void)0;
    (void)0;
    (void)0;
    (void)0;
    return ((size >> 3) << 16) | (0xffff & (addr >> 3));
}

static inline u32 GetUpperSideAlignmentSize_(u32 addr, BOOL b4Pltt)
{
    if (b4Pltt) {
        return 7 & (8 - (addr & 7));
    } else {
        return 0xf & (0x10 - (addr & 0xf));
    }
}

static inline u32 GetLowerSideAlignmentSize_(u32 addr, BOOL b4Pltt)
{
    if (b4Pltt) {
        return addr & 7;
    } else {
        return addr & 0xf;
    }
}

static inline u32 GetCapacity_(void)
{
    (void)0;
    return data_02047364.hiAddr - data_02047364.loAddr;
}

static inline BOOL AllocFromLo_(u32 szByte, BOOL b4Pltt, u32 *pResAddr)
{
    const u32 addr = data_02047364.loAddr;
    const u32 alignment = GetUpperSideAlignmentSize_(addr, b4Pltt);
    const u32 increase = szByte + alignment;

    (void)0;
    (void)0;

    if (GetCapacity_() >= increase) {
        const u32 tail = data_02047364.loAddr + increase;

        if (b4Pltt) {
            if (tail > NNS_GFD_4PLTT_MAX_ADDR) {
                return FALSE;
            }
        }

        *pResAddr = data_02047364.loAddr + alignment;
        data_02047364.loAddr += increase;
        return TRUE;
    } else {
        return FALSE;
    }
}

static inline BOOL AllocFromHi_(u32 szByte, BOOL b4Pltt, u32 *pResAddr)
{
    (void)0;
    (void)0;

    if (data_02047364.hiAddr >= szByte) {
        const u32 addr = data_02047364.hiAddr - szByte;
        const u32 alignment = GetLowerSideAlignmentSize_(addr, b4Pltt);
        const u32 increase = szByte + alignment;

        if (GetCapacity_() >= increase) {
            const u32 tail = data_02047364.hiAddr;

            if (b4Pltt) {
                if (tail > NNS_GFD_4PLTT_MAX_ADDR) {
                    return FALSE;
                }
            }

            data_02047364.hiAddr -= increase;
            *pResAddr = data_02047364.hiAddr;
            return TRUE;
        }
    }
    return FALSE;
}

NNSGfdPlttKey func_020111c0(u32 szByte, BOOL bPltt4, u32 allocFrom)
{
    u32 addr = 0;
    BOOL result = FALSE;

    (void)0;
    {
        szByte = NNSi_GfdGetPlttKeyRoundupSize(szByte);
        if (szByte >= NNS_GFD_PLTTSIZE_MAX) {
            (void)0;
            return NNS_GFD_ALLOC_ERROR_PLTTKEY;
        }
        (void)0;
    }

    if (allocFrom == NNS_GFD_ALLOC_FROM_LOW) {
        result = AllocFromLo_(szByte, bPltt4, &addr);
    } else {
        result = AllocFromHi_(szByte, bPltt4, &addr);
    }

    if (result) {
        return NNS_GfdMakePlttKey(addr, szByte);
    }
    (void)0;
    return NNS_GFD_ALLOC_ERROR_PLTTKEY;
}
