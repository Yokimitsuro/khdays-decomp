/* ov002 camera shots, 0x0207e764-0x0207e830.
 *
 * Seventeen {distance, height, scale} triples in Q12, read by
 * Ov002_GetCameraDistance. Distance runs 0.0625 to 10.0, height is signed, and scale
 * is 1.0 in all but four shots.
 *
 * The first triple straddles two symbol boundaries: the delink gives its first two
 * words their own symbols because the code reaches them directly, so the third array
 * carries the remaining word of that triple followed by the sixteen whole ones.
 */

typedef int fx32;

typedef struct {
    fx32 nDistance;
    fx32 nHeight;
    fx32 nScale;
} Ov002CameraShot;

typedef struct {
    fx32 nFirstShotScale;
    Ov002CameraShot aShots[16];
} Ov002CameraShotTail;

fx32 data_ov002_0207e764[1] = { 0x5000 };

fx32 data_ov002_0207e768[1] = { 0x1a00 };

Ov002CameraShotTail data_ov002_0207e76c = {
    0x1000,
    {
        { 0x5000, 0xfffff800, 0x1a00 },
        { 0x5000, 0x1600, 0x1000 },
        { 0x4000, 0x1800, 0x1000 },
        { 0x5000, 0, 0x14cc },
        { 0x5000, 0xfffff380, 0x1000 },
        { 0x2800, 0x1a00, 0x1000 },
        { 0x100, 0, 0x1000 },
        { 0x3400, 0x300, 0x14cc },
        { 0x5000, 0xfffffc00, 0x1c00 },
        { 0x6800, 0xffffe800, 0x2800 },
        { 0xa000, 0xffffd800, 0x2800 },
        { 0x2400, 0xfffff800, 0x1000 },
        { 0x2800, 0xfffff800, 0x1000 },
        { 0x3000, 0xfffff800, 0x1000 },
        { 0x3800, 0xfffff000, 0x1000 },
        { 0x3800, 0x1000, 0x1000 },
    },
};
