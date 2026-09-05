typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct Ov008ListEntry {
    u8 pad_0000[0x84];
    u32 flags;
} Ov008ListEntry;

extern void *NNS_FndGetNextListObject(void *list, void *previous);
extern void MI_CpuFill8(void *destination, int value, int size);
extern void MI_CpuCopy8(const void *source, void *destination, int size);
extern Point *func_ov008_02054820(int owner, Ov008ListEntry *entry);
extern Point *func_ov008_0205489c(int owner, Ov008ListEntry *entry);
extern void func_ov008_02054858(
    int owner, Ov008ListEntry *entry, const Point *position);

void func_ov008_020549dc(int owner, int xOffset, int clearBase)
{
    Point finalPosition;
    Point basePosition;
    Ov008ListEntry *entry;

    entry = NNS_FndGetNextListObject((void *)(owner + 0x4a38), 0);
    if (entry == 0) {
        return;
    }

    do {
        if (((entry->flags << 28) >> 31) == 0) {
            Point *currentPosition;

            if (clearBase != 0) {
                MI_CpuFill8(&basePosition, 0, sizeof(basePosition));
            } else {
                Point *source = func_ov008_0205489c(owner, entry);
                MI_CpuCopy8(source, &basePosition, sizeof(basePosition));
            }

            currentPosition = func_ov008_02054820(owner, entry);
            finalPosition.x = basePosition.x + xOffset;
            finalPosition.y = currentPosition->y;
            func_ov008_02054858(owner, entry, &finalPosition);
        }

        entry = NNS_FndGetNextListObject(
            (void *)(owner + 0x4a38), entry);
    } while (entry != 0);
}
