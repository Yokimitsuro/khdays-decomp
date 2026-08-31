/* Apply a pixel offset to a result sprite using a 20.12 vector. */
typedef struct Vec2Fx32 { int nX, nY; } Vec2Fx32;
typedef struct Ov005SpriteManager { char data[0x4a80]; } Ov005SpriteManager;
typedef struct Ov005ResultContext { char unknown00[0x54]; Ov005SpriteManager spriteManager; } Ov005ResultContext;
extern Ov005ResultContext *data_ov005_0205b810;
extern void *func_ov005_0204e0d0(Ov005SpriteManager *, int);
extern void func_ov005_0204e1e0(Ov005SpriteManager *, void *, Vec2Fx32 *);
void func_ov005_02055594(int entryId, int xPixels, int yPixels) {
    Vec2Fx32 offset;
    void *entry;
    offset.nX = xPixels << 12;
    offset.nY = yPixels << 12;
    entry = func_ov005_0204e0d0(&data_ov005_0205b810->spriteManager, entryId);
    func_ov005_0204e1e0(&data_ov005_0205b810->spriteManager, entry, &offset);
}
