typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;

typedef struct Ov000TileAsset {
    u8 pad_0000[8];
    const u16 *tiles;
} Ov000TileAsset;

typedef struct Ov000TileDrawRequest {
    u8 pad_0000[2];
    s16 destinationX;
    s16 destinationY;
    u16 width;
    u16 height;
    s16 sourceX;
    s16 sourceY;
    u8 pad_000e[2];
    int kind;
    u8 pad_0014[4];
    const Ov000TileAsset *asset;
} Ov000TileDrawRequest;

typedef struct Ov000TileBuffer {
    u8 data[0x800];
} Ov000TileBuffer;

typedef struct Ov000ListSceneContext {
    u8 pad_0000[0x966c];
    u16 transferFlags;
    u8 pad_966e[0x2a2];
    Ov000TileBuffer tileBuffers[7];
} Ov000ListSceneContext;

extern Ov000ListSceneContext *NNSi_FndGetCurrentRootHeap(void);
extern void func_02013484(
    void *destination,
    const u16 *source,
    u16 width,
    u16 height,
    int destinationX,
    int destinationY,
    int tileWidth,
    int tileHeight,
    int sourceX,
    int sourceY
);

void func_ov000_02059524(const Ov000TileDrawRequest *request) {
    Ov000ListSceneContext *context = NNSi_FndGetCurrentRootHeap();
    int bufferIndex;
    unsigned int sourceX;
    unsigned int sourceY;
    void *destination;

    switch (request->kind) {
    case 9:
        bufferIndex = 0;
        break;
    case 10:
        bufferIndex = 1;
        break;
    case 11:
        bufferIndex = 2;
        break;
    case 25:
        bufferIndex = 4;
        break;
    case 26:
        bufferIndex = 5;
        break;
    case 27:
        bufferIndex = 6;
        break;
    default:
        bufferIndex = -1;
        break;
    }

    if (bufferIndex < 0 || bufferIndex >= 7) {
        return;
    }

    destination = &context->tileBuffers[bufferIndex];
    sourceX = request->sourceX;
    if (sourceX == -1) {
        sourceX = (unsigned int)request->asset->tiles[0] >> 3;
    }
    sourceY = request->sourceY;
    if (sourceY == -1) {
        sourceY = (unsigned int)request->asset->tiles[1] >> 3;
    }

    func_02013484(destination,
                  request->asset->tiles,
                  request->width,
                  request->height,
                  request->destinationX,
                  request->destinationY,
                  0x20,
                  0x18,
                  sourceX,
                  sourceY);
    context->transferFlags |= 1 << bufferIndex;
}
