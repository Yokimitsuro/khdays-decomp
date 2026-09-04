/* ov002 HUD record surfaces and peer slot ids, 0x0207e4f8-0x0207e640.
 *
 * Seven ten-word records read by Ov002_BuildHudRecordSurfaces. Only the first five
 * words differ between them; the last five are 15, 0, 22, 0, 32 in every record.
 *
 * After them, sixteen id triples read by Ov002_LoadPeerIntoSlot. Each is a base id
 * with the same id plus 13 and plus 26, and 255 marks the end of the used entries.
 */

typedef unsigned char u8;

typedef struct {
    int nSlot;
    int nRow;
    int nColumn;
    int nLines;
    int nTextId;
    int nPalette;
    int nUnused0;
    int nHeight;
    int nUnused1;
    int nStride;
} Ov002HudRecord;

typedef struct {
    u8 nBase;
    u8 nMid;
    u8 nHigh;
} Ov002PeerIds;

const Ov002HudRecord data_ov002_0207e4f8 = {
    19, 18, 13, 4, 971,
    15, 0, 22, 0, 32,
};

const Ov002HudRecord data_ov002_0207e520 = {
    20, 2, 30, 4, 867,
    15, 0, 22, 0, 32,
};

const Ov002HudRecord data_ov002_0207e548 = {
    3, 2, 30, 4, 747,
    15, 0, 22, 0, 32,
};

const Ov002HudRecord data_ov002_0207e570 = {
    8, 18, 13, 4, 867,
    15, 0, 22, 0, 32,
};

const Ov002HudRecord data_ov002_0207e598 = {
    0, 3, 21, 3, 666,
    15, 0, 22, 0, 32,
};

const Ov002HudRecord data_ov002_0207e5c0 = {
    0, 25, 6, 3, 729,
    15, 0, 22, 0, 32,
};

const Ov002HudRecord data_ov002_0207e5e8 = {
    13, 18, 13, 4, 919,
    15, 0, 22, 0, 32,
};

const Ov002PeerIds data_ov002_0207e610[16] = {
    {   1,  14,  27 },
    {   2,  15,  28 },
    {   7,  20,  33 },
    {  10,  23,  36 },
    {   3,  16,  29 },
    {   8,  21,  34 },
    {   9,  22,  35 },
    {   5,  18,  31 },
    {   6,  19,  32 },
    {   4,  17,  30 },
    {  11,  24,  37 },
    {   1,  14,  27 },
    {   1,  14,  27 },
    { 255, 255, 255 },
    {  13,  26,  39 },
    {   0,   0,   0 },
};
