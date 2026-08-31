/* Select decimal digit sequences and hide slots beyond the requested width. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef struct Ov005SpriteManager { char data[0x4a80]; } Ov005SpriteManager;
typedef struct Ov005ResultContext { char unknown00[0x54]; Ov005SpriteManager spriteManager; } Ov005ResultContext;
extern Ov005ResultContext *data_ov005_0205b810;
extern int func_ov005_020578c4(int);
extern int func_ov005_020578f4(int, u32);
extern void *func_ov005_0204e0d0(Ov005SpriteManager *, int);
extern void func_ov005_0204e3bc(Ov005SpriteManager *, void *, u32);
extern void func_ov005_0204e29c(Ov005SpriteManager *, void *, int);
void func_ov005_02055480(u32 value, int firstEntryId, int capacity, int minimumDigits) {
    Ov005ResultContext *context = data_ov005_0205b810;
    u8 index, digitCount;
    digitCount = func_ov005_020578c4(value);
    for (index = 0; index < capacity; index++) {
        void *entry = func_ov005_0204e0d0(&context->spriteManager, firstEntryId + index);
        func_ov005_0204e3bc(&context->spriteManager, entry, (u8)func_ov005_020578f4(index, value));
        if (index < digitCount) func_ov005_0204e29c(&context->spriteManager, entry, 1);
        else func_ov005_0204e29c(&context->spriteManager, entry, index < minimumDigits);
    }
}
