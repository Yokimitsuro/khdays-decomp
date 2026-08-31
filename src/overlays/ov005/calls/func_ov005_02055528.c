/* Select a sequence on a result sprite's slots and make the entry visible. */
typedef struct Ov005SpriteManager { char data[0x4a80]; } Ov005SpriteManager;
typedef struct Ov005ResultContext { char unknown00[0x54]; Ov005SpriteManager spriteManager; } Ov005ResultContext;
extern Ov005ResultContext *data_ov005_0205b810;
extern void *func_ov005_0204e0d0(Ov005SpriteManager *, int);
extern void func_ov005_0204e3bc(Ov005SpriteManager *, void *, unsigned int);
extern void func_ov005_0204e29c(Ov005SpriteManager *, void *, int);
void func_ov005_02055528(int entryId, unsigned int sequenceIndex) {
    void *entry = func_ov005_0204e0d0(&data_ov005_0205b810->spriteManager, entryId);
    func_ov005_0204e3bc(&data_ov005_0205b810->spriteManager, entry, sequenceIndex);
    entry = func_ov005_0204e0d0(&data_ov005_0205b810->spriteManager, entryId);
    func_ov005_0204e29c(&data_ov005_0205b810->spriteManager, entry, 1);
}
