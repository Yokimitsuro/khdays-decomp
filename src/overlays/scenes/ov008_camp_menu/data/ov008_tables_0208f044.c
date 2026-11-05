/* ov008 .rodata tables, 0x0208f044-0x0208f080.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_0208f044: Ov008_BindUiAnimTracks
 *   data_ov008_0208f050: Ov008_UpdatePanelBrightnessTweens, Ov008_WorldMap_InitPanelContext, Ov008_ReleaseRowSurfaces, Ov008_DrawMenuPanels
 */

#include "nitro/types.h"

const u8 data_ov008_0208f044[12] = {
    0, 0, 1, 0, 2, 0, 4, 0, 3, 0, 0, 0,
};

const u8 data_ov008_0208f050[48] = {
    62, 0, 0, 0, 63, 0, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0,
    13, 0, 0, 0, 14, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255,
    65, 0, 0, 0, 1, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255,
};
