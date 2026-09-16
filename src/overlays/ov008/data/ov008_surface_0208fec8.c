/* ov008 surface configuration data_ov008_0208fec8, 0x0208fec8-0x0208fedc (.rodata).
 *
 * Copied into a 0x4c-byte surface by 0205546c, which allocates the cell,
 * sprite and slot arrays from the three counts and keeps the two hooks.
 * This one configures the shop container's surface (0208247c).
 */

typedef void (*Ov008SurfaceFn)(void);

typedef struct Ov008SurfaceConfig {
    int nCellCount;           /* 0x00: 0x38-byte cells */
    int nSpriteCount;         /* 0x04: 0x30-byte sprites */
    int nSlotCount;           /* 0x08: 16-byte slots */
    Ov008SurfaceFn pfnDraw;   /* 0x0c */
    Ov008SurfaceFn pfnRelease; /* 0x10 */
} Ov008SurfaceConfig;

extern void func_ov008_0208245c(void);
extern void func_ov008_0208246c(void);

const Ov008SurfaceConfig data_ov008_0208fec8 = {
    105,  /* nCellCount */
    1,  /* nSpriteCount */
    28,  /* nSlotCount */
    func_ov008_0208245c,  /* pfnDraw */
    func_ov008_0208246c,  /* pfnRelease */
};
