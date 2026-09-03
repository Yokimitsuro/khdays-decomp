/* ov002 panel row effect steps, 0x0207e214-0x0207e358.
 *
 * Three contiguous runs of nine {from, to, frames} steps, all read by
 * Ov002_SceneStepPanelRowFx. from and to are fixed point and frames is a plain frame
 * count; each run is one nine-phase sequence.
 */

typedef int fx32;

typedef struct {
    fx32 nFrom;
    fx32 nTo;
    int nFrames;
} Ov002PanelRowStep;

const Ov002PanelRowStep data_ov002_0207e214[9] = {
    { 0, 0x1f000, 150 },
    { 0x1f000, 0x1f000, 180 },
    { 0x1f000, 0, 330 },
    { 0, 0x1f000, 130 },
    { 0x1f000, 0x1f000, 170 },
    { 0x1f000, 0, 300 },
    { 0, 0x1f000, 130 },
    { 0x1f000, 0x1f000, 170 },
    { 0x1f000, 0, 200 },
};

const Ov002PanelRowStep data_ov002_0207e280[9] = {
    { 0, 0x5ec, 150 },
    { 0x5ec, 0x5ec, 180 },
    { 0x5ec, 0x5ec, 330 },
    { 0, 0x75c, 130 },
    { 0x75c, 0x75c, 170 },
    { 0x75c, 0x75c, 300 },
    { 0, 0x75c, 130 },
    { 0x75c, 0x75c, 170 },
    { 0x75c, 0x75c, 200 },
};

const Ov002PanelRowStep data_ov002_0207e2ec[9] = {
    { 0xfb1e0000, 0, 660 },
    { 0xfb1e0000, 0, 660 },
    { 0xfb1e0000, 0, 660 },
    { 0xfb9b0000, 0xfec78000, 630 },
    { 0xfb9b0000, 0xfec78000, 630 },
    { 0xfb9b0000, 0xfec78000, 630 },
    { 0xfb5c8000, 0xfd8f0000, 500 },
    { 0xfb5c8000, 0xfd8f0000, 500 },
    { 0xfb5c8000, 0xfd8f0000, 500 },
};
