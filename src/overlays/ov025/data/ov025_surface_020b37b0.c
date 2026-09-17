/* ov025 surface configuration data_ov025_020b37b0, 0x020b37b0-0x020b37c4 (.rodata).
 *
 * Copied into a 0x4c-byte surface which allocates the cell, sprite and slot
 * arrays from the three counts and keeps the two hooks.  This one configures
 * the records context's surface (Ov025_SetupContext 02083e84: 0x100 cells, 32 sprites, 32 slots, hooks 02083dec / 02083dfc).
 */

typedef void (*Ov008SurfaceFn)(void);

typedef struct Ov008SurfaceConfig {
    int nCellCount;           /* 0x00: 0x38-byte cells */
    int nSpriteCount;         /* 0x04: 0x30-byte sprites */
    int nSlotCount;           /* 0x08: 16-byte slots */
    Ov008SurfaceFn pfnDraw;   /* 0x0c */
    Ov008SurfaceFn pfnRelease; /* 0x10 */
} Ov008SurfaceConfig;

extern void func_ov025_02083dec(void);
extern void func_ov025_02083dfc(void);

const Ov008SurfaceConfig data_ov025_020b37b0 = {
    256,  /* nCellCount */
    32,  /* nSpriteCount */
    32,  /* nSlotCount */
    func_ov025_02083dec,  /* pfnDraw */
    func_ov025_02083dfc,  /* pfnRelease */
};
