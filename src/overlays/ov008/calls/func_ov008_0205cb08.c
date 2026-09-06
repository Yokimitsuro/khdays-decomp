/* Clear and release the temporary grid cells tracked by the ov008 menu. */
extern int  NNS_FndGetNextListObject(void *list, int obj);
extern void NNS_FndRemoveListObject(void *list, int obj);
extern void NNSi_FndFreeFromDefaultHeap(int p);

typedef struct Ov008GridDisplayCell {
    char unknown00[0x1e];
    unsigned short displayState;
    char unknown20[0x08];
} Ov008GridDisplayCell;

typedef struct Ov008GridMenuContextView {
    char pad0000[0x6c];
    unsigned short wCol;
    unsigned short wRow;
    char pad0070[0x10a0 - 0x70];
    Ov008GridDisplayCell gridDisplayCells[9][5];
} Ov008GridMenuContextView;

typedef struct Ov008TrackedGridNode {
    int entry;
    int columnOffset;
    int rowOffset;
} Ov008TrackedGridNode;

void func_ov008_0205cb08(int param_1) {
    int node = NNS_FndGetNextListObject((void *)(param_1 + 0x19b8), 0);
    int next;
    int row;
    if (node != 0) {
        row = param_1;
        do {
            next = NNS_FndGetNextListObject((void *)(param_1 + 0x19b8), node);
            ((Ov008GridMenuContextView *)param_1)->gridDisplayCells
                [(unsigned int)((Ov008GridMenuContextView *)param_1)->wRow + ((Ov008TrackedGridNode *)node)->rowOffset]
                [(unsigned int)((Ov008GridMenuContextView *)param_1)->wCol + ((Ov008TrackedGridNode *)node)->columnOffset]
                .displayState = 0x1f;
            NNS_FndRemoveListObject((void *)(param_1 + 0x19b8), node);
            if (node != 0) {
                NNSi_FndFreeFromDefaultHeap(node);
            }
            *(int *)(row + 0x184c) = 0;
            node = next;
            row = row + 0x28;
        } while (next != 0);
    }
}
