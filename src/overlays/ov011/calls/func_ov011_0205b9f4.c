/* func_ov011_0205b9f4 -- Ov011_BlitPaneTiles (356 B, ARM, 5 relocs).
 *
 * Copies a title pane's tileset rows into the scene's VRAM tilemap. The pane record
 * lives at pane+4: rec[0] = row count, rec[1] = stride (tiles per source row),
 * rec[0x14] = the tile-pixel data. The destination is scene+0x91c for pane 0 and
 * scene+0x91c+0x10940 for pane 1 (paneIdx picks the block). Each of `rows` source
 * rows is copied to destination row `dstRow` (wrapping at 0x20 in the 32x32 tilemap);
 * when a row straddles the 0x20 column wrap it is split into a head + tail copy. The
 * per-row width is clamped to 9 (stride <= 9) or 10, and the row count to 0x1a. After
 * the rows are staged, a GFX transfer command (6 for pane 0, 0x16 for pane 1) is
 * enqueued for the pane's tilemap block.
 *
 * Codegen notes (mwcc 3.0/139, byte-exact): three source-shape choices carry the match,
 * NOT a compiler build -- confirmed the whole "retail 3.0>=140" theory for this cluster
 * was wrong. (1) Clamp dstRow (`if (dstRow < 0) dstRow = 0;`) as the FIRST statement,
 * before reading the pane record: this makes mwcc keep the pane pointer (param_1) in fp
 * across the loop (`mov fp,r0` first) instead of spilling it -- the whole register stream
 * cascades from it. (2) Declare `i` before `src` so the loop counter takes r4 and the
 * running source pointer takes r5. (3) In the loop tail advance `src` before bumping the
 * counters, so the pane reload schedules early like the ROM. Modelling the tiles as a
 * 0x40-byte `Tile` (indexed, not `int* + i*0x40`) is what removed the earlier size gap.
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Tile { int px[16]; } Tile;  /* 0x40 bytes = one 8x8 4bpp tile */

extern int  data_ov011_0205e960[2];        /* [1] = pScene */
extern void MIi_CpuCopy32(const void *src, void *dst, int size);
extern int  GFXi_EnqueueCommand(int a, int b, int c, int d);

/* The pane record pointer lives at pane+4; accessed inline (never cached in a local) so
 * mwcc re-reads it via param_1 each loop iteration -- matching the ROM's `ldr r3,[fp,#4]`. */
#define PANE  (*(u16 **)(pane + 4))

void func_ov011_0205b9f4(int pane, int paneIdx, int dstCol, int dstRow)
{
    u32 stride;
    u32 rows;
    int copyW;
    int i;
    Tile *src;

    if (dstRow < 0)
        dstRow = 0;
    stride = PANE[1];
    rows = *PANE;
    copyW = paneIdx;
    if (stride <= 9)
        copyW = 9;
    else
        copyW = 10;
    if ((int)(dstRow + rows) >= 0x1a)
        rows = 0x1a;
    src = (Tile *)*(int *)(PANE + 10) + (dstRow * stride + dstCol);
    i = 0;
    if (0 < (int)rows) {
        int headW = 0x20 - dstCol;
        int paneOff = paneIdx * 0x10940;
        do {
            Tile *dst;
            if (dstRow == 0x20)
                dstRow = 0;
            dst = (Tile *)(data_ov011_0205e960[1] + 0x91c + paneOff) +
                  (dstCol + dstRow * 0x20);
            if (dstCol + copyW <= 0x20) {
                MIi_CpuCopy32(src, dst, copyW << 6);
            } else {
                MIi_CpuCopy32(src, dst, headW * 0x40);
                MIi_CpuCopy32(src + headW, dst - (0x20 - copyW),
                              (copyW - headW) * 0x40);
            }
            src = src + (u32)PANE[1];
            i = i + 1;
            dstRow = dstRow + 1;
        } while (i < (int)rows);
    }
    GFXi_EnqueueCommand(paneIdx == 0 ? 6 : 0x16, 0,
                        data_ov011_0205e960[1] + 0x91c + paneIdx * 0x10940, 0x10000);
}
