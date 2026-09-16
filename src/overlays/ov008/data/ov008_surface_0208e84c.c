/* ov008 surface configuration data_ov008_0208e84c, 0x0208e84c-0x0208e860 (.rodata).
 *
 * Copied into a 0x4c-byte surface by 0205546c, which allocates the cell,
 * sprite and slot arrays from the three counts and keeps the two hooks.
 * This one configures the campaign menu's surface (Ov008_InitCampaignMenuContext).
 */

typedef void (*Ov008SurfaceFn)(void);

typedef struct Ov008SurfaceConfig {
    int nCellCount;           /* 0x00: 0x38-byte cells */
    int nSpriteCount;         /* 0x04: 0x30-byte sprites */
    int nSlotCount;           /* 0x08: 16-byte slots */
    Ov008SurfaceFn pfnDraw;   /* 0x0c */
    Ov008SurfaceFn pfnRelease; /* 0x10 */
} Ov008SurfaceConfig;

extern void func_ov008_0204ffc4(void);
extern void func_ov008_0204ffd4(void);

const Ov008SurfaceConfig data_ov008_0208e84c = {
    256,  /* nCellCount */
    32,  /* nSpriteCount */
    32,  /* nSlotCount */
    func_ov008_0204ffc4,  /* pfnDraw */
    func_ov008_0204ffd4,  /* pfnRelease */
};
