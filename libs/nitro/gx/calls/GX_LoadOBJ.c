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


/* NitroSDK GX VRAM loaders (gx_load2d.c / gx_load3d.c, gxdma.h). */
typedef void (*MIDmaCallback)(void *);
#define GX_DMA_NOT_USE      ((u32) ~0)
#define GX_CPU_FASTER32_SIZE 0x30
#define HW_OBJ_VRAM         0x06400000
#define HW_DB_OBJ_VRAM      0x06600000
#define HW_LCDC_VRAM_E      0x06880000
#define HW_LCDC_VRAM_F      0x06890000
#define HW_LCDC_VRAM_G      0x06894000
typedef enum {
    GX_VRAM_BGEXTPLTT_NONE    = 0x0000,
    GX_VRAM_BGEXTPLTT_01_F    = 0x0020,
    GX_VRAM_BGEXTPLTT_23_G    = 0x0040,
    GX_VRAM_BGEXTPLTT_0123_E  = 0x0010,
    GX_VRAM_BGEXTPLTT_0123_FG = 0x0060
} GXVRamBGExtPltt;
typedef enum {
    GX_VRAM_OBJEXTPLTT_NONE = 0x0000,
    GX_VRAM_OBJEXTPLTT_0_F  = 0x0020,
    GX_VRAM_OBJEXTPLTT_0_G  = 0x0040
} GXVRamOBJExtPltt;
typedef int GXVRamTex;

extern u32 data_020422b8;   /* GXi_DmaId */
#define GXi_DmaId data_020422b8
extern void MI_DmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size);
extern void MI_DmaCopy32Async(u32 dmaNo, const void *src, void *dest, u32 size, MIDmaCallback callback, void *arg);
extern void MIi_CpuCopy32(const void *src, void *dest, u32 size);
#define MI_CpuCopy32 MIi_CpuCopy32
/* This SDK names the bank-release helpers GX_DisableBankFor*; 4.x calls them GX_ResetBankFor*. */
extern GXVRamBGExtPltt GX_DisableBankForBGExtPltt(void);
#define GX_ResetBankForBGExtPltt GX_DisableBankForBGExtPltt
extern GXVRamOBJExtPltt GX_DisableBankForOBJExtPltt(void);
#define GX_ResetBankForOBJExtPltt GX_DisableBankForOBJExtPltt
/* Real inline functions, as in the SDK headers: the value they return stays a variable (`ptr`
 * lands in ip and feeds both branches) where a macro constant would fold into each add. */
static inline void *G2_GetOBJCharPtr(void) { return (void *)HW_OBJ_VRAM; }
static inline void *G2S_GetOBJCharPtr(void) { return (void *)HW_DB_OBJ_VRAM; }
#define GX_RegionCheck_OBJ(a, b)
#define GX_RegionCheck_SubOBJ(a, b)
#define GX_RegionCheck_Tex(t, a, b)

static inline void GXi_DmaCopy32(u32 dmaNo, const void *src, void *dest, u32 size)
{
    if (dmaNo != GX_DMA_NOT_USE && size > GX_CPU_FASTER32_SIZE) {
        MI_DmaCopy32(dmaNo, src, dest, size);
    } else {
        MI_CpuCopy32(src, dest, size);
    }
}

static inline void GXi_DmaCopy32Async(u32 dmaNo, const void *src, void *dest, u32 size,
                                      MIDmaCallback callback, void *arg)
{
    if (dmaNo != GX_DMA_NOT_USE) {
        MI_DmaCopy32Async(dmaNo, src, dest, size, callback, arg);
    } else {
        MI_CpuCopy32(src, dest, size);
    }
}

/* GX_LoadOBJ -- NitroSDK gx_load2d.c. */
void GX_LoadOBJ (const void *pSrc, u32 offset, u32 szByte)
{
	u32 ptr;


	ptr = (u32)G2_GetOBJCharPtr();

	GX_RegionCheck_OBJ(ptr + offset, ptr + offset + szByte);
	GXi_DmaCopy32(GXi_DmaId, pSrc, (void *)(ptr + offset), szByte);
}
