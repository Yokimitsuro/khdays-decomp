typedef unsigned char u8;
typedef unsigned short u16;

typedef struct MobiClipHeader {
    u16 destinationX;
    u16 destinationY;
    u16 macroblockWidth;
    u16 macroblockHeight;
    u16 tileBase;
    u16 palette;
    u16 flags;
    u16 cropLeft;
    u16 cropRight;
    u16 cropTop;
    u16 cropBottom;
} MobiClipHeader;

typedef struct MobiClipOpenRequest {
    char *stream0;
    char *stream1;
    char *stream2;
    void (*frameCallback)(void);
} MobiClipOpenRequest;

extern char *data_ov012_0205cb20;
extern void func_ov012_0205accc(void);
extern void func_ov012_0205bb3c(void *renderer, int layer, void *font,
                                MobiClipHeader *header);
extern u16 *func_02024950(int layer);
extern void func_02014174(u16 *tilemap, int width, int height, int x, int y,
                          int mapWidth, u16 tile, int palette);
extern void func_ov012_0205bba4(void *renderer, int ready);
extern void func_02031574(int value);
extern void func_02030e64(int value);
extern int func_ov008_020846c0(MobiClipOpenRequest *request);

void func_ov012_0205b0cc(char *streamName)
{
    char *context;
    MobiClipOpenRequest request;
    MobiClipHeader header;

    context = data_ov012_0205cb20;
    request.stream0 = 0;
    request.stream1 = streamName;
    request.stream2 = 0;
    request.frameCallback = func_ov012_0205accc;

    *(int *)(context + 0x8bdc) = 1;

    header.destinationX = 0;
    header.destinationY = 0x14;
    header.macroblockWidth = 0x20;
    header.macroblockHeight = 2;
    header.tileBase = 1;
    header.palette = 0xd;
    header.flags = 0;
    header.cropLeft = 0;
    header.cropRight = 0;
    header.cropTop = 3;
    header.cropBottom = 0;

    func_ov012_0205bb3c(context + 0x8b4c, 4, context + 0x8b40, &header);

    func_02014174(func_02024950(5),
                  header.macroblockWidth, header.macroblockHeight,
                  header.destinationX, header.destinationY,
                  0x20, header.tileBase, 0xe);
    func_02014174(func_02024950(6),
                  header.macroblockWidth, header.macroblockHeight,
                  header.destinationX, header.destinationY,
                  0x20, header.tileBase, 0xe);

    func_ov012_0205bba4(context + 0x8b4c, 1);
    func_02031574(1);
    func_02030e64(1);

    if (func_ov008_020846c0(&request) == 0) {
        *(u16 *)(context + 2) |= 2;
    }
}
