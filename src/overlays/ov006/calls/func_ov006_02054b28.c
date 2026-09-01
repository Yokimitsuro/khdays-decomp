/* Copy or erase a clipped Mission Mode tilemap rectangle and mark its cell
 * buffer dirty for the next VRAM flush. */
#pragma opt_strength_reduction off
#pragma opt_dead_assignments off

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct NNSG2dScreenData {
    u16 screenWidth;
    u16 screenHeight;
    u16 colorMode;
    u16 screenFormat;
    u32 szByte;
    u32 rawData[1];
} NNSG2dScreenData;

typedef struct Ov006ResourceTrackerAux {
    u8 opaque[8];
    NNSG2dScreenData *screen;
    int active;
} Ov006ResourceTrackerAux;

typedef struct Ov006TileBlitRequest {
    u16 id;
    short destinationX;
    short destinationY;
    u16 sourceX;
    u16 sourceY;
    short width;
    short height;
    u8 reserved0e[2];
    int bufferHandle;
    int active;
    Ov006ResourceTrackerAux *asset;
    u8 reserved1c[0x1c];
} Ov006TileBlitRequest;

typedef struct Ov006CharacterSelectContext {
    u8 opaque0000[0x94cc];
    u16 *cellBuffers[8];
    u8 opaque94ec[0x84];
    u8 dirtyCellBufferMask;
} Ov006CharacterSelectContext;

extern Ov006CharacterSelectContext *data_ov006_02056664;
extern void MIi_CpuCopy16(const void *source, void *destination, u32 size);
extern void MIi_CpuClear16(u16 value, void *destination, u32 size);

void func_ov006_02054b28(int entryAddress, int copy) {
    NNSG2dScreenData *screen;
    int row;
    u32 sourceX;
    u32 sourceWidth;
    u32 sourceY;
    Ov006TileBlitRequest *request = (Ov006TileBlitRequest *)entryAddress;
    u16 *destination;
    u32 destinationX;
    int extent;
    int width;
    u32 destinationY;
    {
    int height;
    int bufferIndex;

    bufferIndex = -1;
    switch (request->bufferHandle) {
    case 8:
        bufferIndex = 0;
        break;
    case 9:
        bufferIndex = 1;
        break;
    case 10:
        bufferIndex = 2;
        break;
    case 11:
        bufferIndex = 3;
        break;
    case 24:
        bufferIndex = 4;
        break;
    case 25:
        bufferIndex = 5;
        break;
    case 26:
        bufferIndex = 6;
        break;
    case 27:
        bufferIndex = 7;
        break;
    }

    destination = 0;
    if (bufferIndex != -1) {
        destination = data_ov006_02056664->cellBuffers[bufferIndex];
    }

    screen = request->asset->screen;
    width = request->width;
    height = request->height;
    sourceWidth = (u32)screen->screenWidth >> 3;
    if (width == -1) {
        width = sourceWidth;
    }
    if (height == -1) {
        height = (u32)screen->screenHeight >> 3;
    }
    sourceX = request->sourceX;
    sourceY = request->sourceY;

    if (request->destinationX < 0) {
        sourceX -= request->destinationX;
        width += request->destinationX;
        destinationX = 0;
    } else {
        destinationX = (u16)request->destinationX;
    }
    extent = destinationX + width;
    if (extent > 32) {
        extent -= 32;
        width -= extent;
    }

    if (request->destinationY < 0) {
        sourceY -= request->destinationY;
        height += request->destinationY;
        destinationY = 0;
    } else {
        destinationY = (u16)request->destinationY;
    }
    extent = destinationY + height;
    if (extent > 24) {
        extent -= 24;
        height -= extent;
    }

    if (copy) {
        for (row = 0; row < height; row++) {
            MIi_CpuCopy16(
                (u16 *)request->asset->screen->rawData +
                    (sourceWidth * (sourceY + row) + sourceX),
                destination + (destinationX + (destinationY << 5)),
                width * 2);
            destinationY++;
        }
    } else {
        sourceY = 0;
        if (height > 0) {
            row = width * 2;
            entryAddress = sourceY;
            do {
                MIi_CpuClear16(
                    entryAddress,
                    destination + (destinationX + (destinationY << 5)),
                    row);
                sourceY++;
                destinationY++;
            } while ((int)sourceY < height);
        }
    }

    extent = entryAddress + row + sourceY;
    data_ov006_02056664->dirtyCellBufferMask |= 1 << bufferIndex;
    }
}