/* Place a result tile by tag and dispatch the tracker's drawing callback. */
typedef struct Ov000TileBlitRequest Ov000TileBlitRequest;
typedef struct Ov000ResourceTracker { char data[76]; } Ov000ResourceTracker;
typedef struct Ov005ResultContext { char unknown00[8]; Ov000ResourceTracker resourceTracker; } Ov005ResultContext;
extern Ov005ResultContext *data_ov005_0205b810;
extern Ov000TileBlitRequest *func_ov005_0204d434(Ov000ResourceTracker *, int);
extern void func_ov005_0204d4a0(Ov000ResourceTracker *, Ov000TileBlitRequest *, int, int);
extern void func_ov005_0204d4c8(Ov000ResourceTracker *, Ov000TileBlitRequest *);
void func_ov005_020562c4(int tileId, int column, int row) {
    Ov005ResultContext *context = data_ov005_0205b810;
    Ov000TileBlitRequest *entry = func_ov005_0204d434(&context->resourceTracker, (unsigned short)tileId);
    func_ov005_0204d4a0(&context->resourceTracker, entry, column, row);
    func_ov005_0204d4c8(&context->resourceTracker, entry);
}
