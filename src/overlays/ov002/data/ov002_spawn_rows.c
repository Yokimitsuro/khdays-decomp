/* ov002 spawn rows, 0x0207e67c-0x0207e6fc.
 *
 * Sixteen four-halfword rows read by Ov002_BuildSpawnRow. The first field carries the
 * entry id, the rest a count and two timings; the last rows are 0xff terminators.
 */

typedef unsigned short u16;

typedef struct {
    u16 nId;
    u16 nCount;
    u16 nDelay;
    u16 nPeriod;
} Ov002SpawnRow;

const Ov002SpawnRow data_ov002_0207e67c[16] = {
    {  4096,    32,   300,    60 },
    {  4105,    16,   600,    60 },
    {  4097,    16,   300,    60 },
    {  4098,    16,   300,    60 },
    {   255,     0,     0,     0 },
    {   255,     0,     0,     0 },
    {  8195,    32, 65535,    60 },
    {  8196,    32, 65535,    60 },
    {  8197,    32, 65535,    60 },
    {  8447,    32,   600,    60 },
    {  8447,    32,   600,    60 },
    {  8447,    32,   600,    60 },
    {   255,     0,     0,     0 },
    {  8202,    32, 65535,    60 },
    {   255,     0,     0,     0 },
    {  8200,    31,     0,     0 },
};
