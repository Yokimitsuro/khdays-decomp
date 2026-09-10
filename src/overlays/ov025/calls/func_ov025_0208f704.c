typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Ov008MenuEntry {
    u8 pad00[0x0c];
    int entryId;
} Ov008MenuEntry;

typedef struct Ov008MenuContext {
    u8 pad0000[0x08];
    int menuMode;
    u8 pad000c[0x10 - 0x0c];
    int menuState;
    u8 pad0014[0x20 - 0x14];
    int selectedSavePage;
    u8 pad0024[0xa4 - 0x24];
    int pendingActionCode;
    u8 pad00a8[0x28c - 0xa8];
    u8 savePageTextRecords;
} Ov008MenuContext;

extern Ov008MenuContext *func_ov025_02084afc(void);
extern void func_ov025_0208f144(Ov008MenuEntry *entry);
extern void *func_ov025_02089894(void *records, int index);
extern void func_ov025_02091070(
    Ov008MenuContext *context, int row, void *text, int mode);
extern void func_02033b78(int arg0, int arg1);
extern void func_ov025_0208f37c(
    Ov008MenuContext *context, int savePage);

void func_ov025_0208f704(Ov008MenuEntry *entry, u32 inputFlags)
{
    Ov008MenuContext *context = func_ov025_02084afc();
    int previousSavePage;
    void *captionRecord;
    int captionRecordIndex;

    if (entry == 0) {
        return;
    }
    if ((inputFlags & 0x40) == 0 && (inputFlags & 0x80) == 0) {
        return;
    }

    func_ov025_0208f144(entry);
    if (context->menuState != 2 || context->menuMode != 1) {
        return;
    }

    switch (context->pendingActionCode) {
    case 0:
        switch (entry->entryId) {
        case 0x50:
            captionRecordIndex = 8;
            break;
        case 0x51:
            captionRecordIndex = 7;
            break;
        case 0x52:
            captionRecordIndex = 9;
            break;
        case 0x53:
            captionRecordIndex = 10;
            break;
        case 0x54:
            captionRecordIndex = 11;
            break;
        default:
            captionRecordIndex = 7;
            break;
        }
        captionRecord = func_ov025_02089894(
            &context->savePageTextRecords, captionRecordIndex);
        func_ov025_02091070(context, 0, captionRecord, 0xf3);
        func_02033b78(0, 0);
        return;

    case 1:
    case 4:
        previousSavePage = context->selectedSavePage;
        switch (entry->entryId) {
        case 0x59:
        case 0x5d:
            context->selectedSavePage = 0;
            break;
        case 0x5a:
        case 0x5e:
            context->selectedSavePage = 1;
            break;
        case 0x5b:
        case 0x5f:
            context->selectedSavePage = 2;
            break;
        default:
            context->selectedSavePage = 0;
            break;
        }
        func_ov025_0208f37c(context, context->selectedSavePage);
        if (previousSavePage == context->selectedSavePage) {
            return;
        }
        func_02033b78(0, 0);
        return;

    case 3:
        break;

    case 6:
        break;

    case 8:
        break;

    default:
        func_02033b78(0, 0);
        return;
    }
}


