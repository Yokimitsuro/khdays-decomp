typedef signed short   s16;
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov009Tilemap {
    u16 pixelWidth;
    u16 pixelHeight;
    u8 pad_04[0x0c - 0x04];
    u16 tiles[1];
} Ov009Tilemap;

typedef struct Ov009TilemapResource {
    u8 pad_00[0x08];
    Ov009Tilemap *tilemap;
} Ov009TilemapResource;

typedef struct Ov009TileBlitRequest {
    u16 field_00;
    s16 destinationX;
    s16 destinationY;
    u16 sourceX;
    u16 sourceY;
    s16 width;
    s16 height;
    u8 pad_0e[0x02];
    int destinationCode;
    u8 pad_14[0x04];
    Ov009TilemapResource *resource;
} Ov009TileBlitRequest;

typedef struct Ov009MenuContext {
    u8 pad_0000[0x95d0];
    int tileGridWidth;
    u8 pad_95d4[0x963c - 0x95d4];
    u8 dirtyTileSlots;
} Ov009MenuContext;

typedef struct Ov009ClipLocals {
    unsigned int copyHeight;
    int clearRow;
    int sourceTileHeight;
} Ov009ClipLocals;

extern Ov009MenuContext *data_ov009_020563e4[];

#define OV009_CONTEXT (data_ov009_020563e4[1])

extern u16 *func_ov009_0204d8a8(int destinationCode, int *slotIndex);
extern int  func_ov009_0204d8ec(int position, int stride,
                                int width, int height);

void func_ov009_0204d924(Ov009TileBlitRequest *request, int copySource)
{
    int slotIndex;
    unsigned int sourceX;
    Ov009ClipLocals clip;
    int sourceTileWidth;
    u16 *source;
    int copyRow;
    int column;
    u16 *destination;
    unsigned int sourceY;
    unsigned int destinationX;
    int destinationY;
    Ov009Tilemap *tilemap;
    int coordinate;

    destination =
        func_ov009_0204d8a8(request->destinationCode, &slotIndex);
    tilemap = request->resource->tilemap;
    sourceTileWidth =
        (unsigned int)tilemap->pixelWidth >> 3;
    clip.sourceTileHeight =
        (unsigned int)tilemap->pixelHeight >> 3;
    int copyWidth = request->width;
    if (copyWidth == -1) {
        copyWidth = sourceTileWidth;
    }
    clip.copyHeight = request->height;
    if (clip.copyHeight == -1) {
        clip.copyHeight = clip.sourceTileHeight;
    }

    sourceX = request->sourceX;
    sourceY = request->sourceY;
    coordinate = request->destinationX;
    if (coordinate < 0) {
        sourceX -= coordinate;
        copyWidth += coordinate;
        destinationX = 0;
    } else {
        destinationX = (u16)coordinate;
    }
    if ((int)(destinationX + copyWidth) >
        OV009_CONTEXT->tileGridWidth) {
        copyWidth -= destinationX + copyWidth -
                     OV009_CONTEXT->tileGridWidth;
    }

    coordinate = request->destinationY;
    if (coordinate < 0) {
        sourceY -= coordinate;
        clip.copyHeight += coordinate;
        destinationY = 0;
    } else {
        destinationY = (u16)coordinate;
    }
    if ((int)(destinationY + clip.copyHeight) > 32) {
        clip.copyHeight -= destinationY + clip.copyHeight - 32;
    }

    if (copySource != 0) {
        source = tilemap->tiles;

        for (copyRow = 0; copyRow < (int)clip.copyHeight; copyRow++) {
            for (column = 0; column < (int)copyWidth; column++) {
                int destinationIndex = func_ov009_0204d8ec(
                    destinationX + column, destinationY,
                    OV009_CONTEXT->tileGridWidth, 32);
                int sourceIndex = func_ov009_0204d8ec(
                    sourceX + column, sourceY + copyRow,
                    sourceTileWidth, clip.sourceTileHeight);
                destination[destinationIndex] =
                    source[sourceIndex];
            }
            destinationY++;
        }
    } else {
        clip.clearRow = 0;
        while (clip.clearRow < (int)clip.copyHeight) {
            for (column = 0; column < (int)copyWidth; column++) {
                int destinationIndex = func_ov009_0204d8ec(
                    destinationX + column, destinationY,
                    OV009_CONTEXT->tileGridWidth, 32);
                destination[destinationIndex] = 0;
            }
            destinationY++;
            clip.clearRow++;
        }
    }

    OV009_CONTEXT->dirtyTileSlots |= 1 << slotIndex;
}
