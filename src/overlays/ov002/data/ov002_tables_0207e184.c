/* ov002 .rodata tables, 0x0207e184-0x0207e214.
 *
 * 6 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Read by Ov002_ResetFollowOffset (0x0207e19c).
 * Read by Ov002_SceneResetPanelFrame (0x0207e184).
 * Read by Ov002_SceneStepPanelCounters (0x0207e190).
 * Read by Ov002_SceneStepPanelFlash (0x0207e1a8, 0x0207e1cc, 0x0207e1f0).
 */

typedef unsigned char u8;
typedef unsigned short u16;

const u8 data_ov002_0207e184[12] = {
    0, 192, 254, 255, 0, 96, 255, 255, 0, 0, 0, 0,
};

const int data_ov002_0207e190[3] = {
    2253, 2376, 2499,
};

const u8 data_ov002_0207e19c[12] = {
    0, 192, 254, 255, 0, 0, 0, 0, 0, 0, 0, 0,
};

const u8 data_ov002_0207e1a8[36] = {
    0, 0, 0, 0, 0, 240, 1, 0, 100, 0, 0, 0, 0, 240, 1, 0,
    0, 240, 1, 0, 200, 0, 0, 0, 0, 240, 1, 0, 0, 0, 0, 0,
    144, 1, 0, 0,
};

const int data_ov002_0207e1cc[9] = {
    0, 1516, 100, 1516, 1516, 200, 1516, 123,
    400,
};

const u8 data_ov002_0207e1f0[36] = {
    0, 0, 192, 249, 0, 0, 224, 252, 100, 0, 0, 0, 0, 0, 224, 252,
    0, 0, 224, 252, 88, 2, 0, 0, 0, 0, 224, 252, 0, 0, 224, 252,
    88, 2, 0, 0,
};
