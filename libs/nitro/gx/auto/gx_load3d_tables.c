/* NitroSDK gx_load3d.c: the texture and texture-palette LCDC start tables (VRAM block addresses >> 12),
 * indexed by the GXVRamTex / GXVRamTexPltt bank masks; read by GX_BeginLoadTex and GX_BeginLoadTexPltt. */
typedef unsigned short u16;
#define HW_LCDC_VRAM     0x06800000
#define HW_VRAM_A_SIZE   0x20000
#define HW_VRAM_B_SIZE   0x20000
#define HW_VRAM_C_SIZE   0x20000
#define HW_VRAM_D_SIZE   0x20000
#define HW_VRAM_E_SIZE   0x10000
#define HW_VRAM_F_SIZE   0x4000
#define HW_LCDC_VRAM_A   (HW_LCDC_VRAM)
#define HW_LCDC_VRAM_B   (HW_LCDC_VRAM_A + HW_VRAM_A_SIZE)
#define HW_LCDC_VRAM_C   (HW_LCDC_VRAM_B + HW_VRAM_B_SIZE)
#define HW_LCDC_VRAM_D   (HW_LCDC_VRAM_C + HW_VRAM_C_SIZE)
#define HW_LCDC_VRAM_E   (HW_LCDC_VRAM_D + HW_VRAM_D_SIZE)
#define HW_LCDC_VRAM_F   (HW_LCDC_VRAM_E + HW_VRAM_E_SIZE)
#define HW_LCDC_VRAM_G   (HW_LCDC_VRAM_F + HW_VRAM_F_SIZE)

/* sTexPlttStartAddrTable */
const u16 data_02041418[8] = {
	0,
	(u16)(HW_LCDC_VRAM_E >> 12),
	(u16)(HW_LCDC_VRAM_F >> 12),
	(u16)(HW_LCDC_VRAM_E >> 12),
	(u16)(HW_LCDC_VRAM_G >> 12),
	0,
	(u16)(HW_LCDC_VRAM_F >> 12),
	(u16)(HW_LCDC_VRAM_E >> 12)
};

/* sTexStartAddrTable: first block, second block (0 when contiguous) and the first block's size. */
const struct {
    u16 blk1;
    u16 blk2;
    u16 szBlk1;
} data_02041428[16] = {
    { 0, 0, 0 },
    { (u16)(HW_LCDC_VRAM_A >> 12), 0, 0 },
    { (u16)(HW_LCDC_VRAM_B >> 12), 0, 0 },
    { (u16)(HW_LCDC_VRAM_A >> 12), 0, 0 },
    { (u16)(HW_LCDC_VRAM_C >> 12), 0, 0 },
    { (u16)(HW_LCDC_VRAM_A >> 12), (u16)(HW_LCDC_VRAM_C >> 12), (u16)(HW_VRAM_A_SIZE >> 12) },
    { (u16)(HW_LCDC_VRAM_B >> 12), 0, 0 },
    { (u16)(HW_LCDC_VRAM_A >> 12), 0, 0 },
    { (u16)(HW_LCDC_VRAM_D >> 12), 0, 0 },
    { (u16)(HW_LCDC_VRAM_A >> 12), (u16)(HW_LCDC_VRAM_D >> 12), (u16)(HW_VRAM_A_SIZE >> 12) },
    { (u16)(HW_LCDC_VRAM_B >> 12), (u16)(HW_LCDC_VRAM_D >> 12), (u16)(HW_VRAM_B_SIZE >> 12) },
	{
		(u16)(HW_LCDC_VRAM_A >> 12),
		(u16)(HW_LCDC_VRAM_D >> 12), (u16)((HW_VRAM_A_SIZE + HW_VRAM_B_SIZE) >> 12)
	},
    { (u16)(HW_LCDC_VRAM_C >> 12), 0, 0 },
    { (u16)(HW_LCDC_VRAM_A >> 12), (u16)(HW_LCDC_VRAM_C >> 12), (u16)(HW_VRAM_A_SIZE >> 12) },
    { (u16)(HW_LCDC_VRAM_B >> 12), 0, 0 },
    { (u16)(HW_LCDC_VRAM_A >> 12), 0, 0 },
};
