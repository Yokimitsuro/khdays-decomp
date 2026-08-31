typedef struct Ov005SelectionState {
    signed char selectedItem,activeRow,firstVisibleItem,unknown03;
    int maxFirstVisibleItem,cachedRowItemCounts[2],scrollThumbHeight;
} Ov005SelectionState;
typedef struct Ov005MenuItemHeader {char opaque00[0x244];int indicatorState;} Ov005MenuItemHeader;
typedef struct Ov005Context {
    char opaque00[0x4bfc];
    Ov005SelectionState selection;
    char opaque4c10[0x5b558];
    Ov005MenuItemHeader *firstItemSlot[2][636];
} Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
int func_ov005_020533d8(int direction) {
    int changed=0;
    Ov005SelectionState *selection=&data_ov005_0205b80c->selection;
    Ov005MenuItemHeader *item;
    switch(direction) {
    case 0x40:
        if(selection->selectedItem>0) {
            selection->selectedItem--;
            changed=1;
        } else if(selection->firstVisibleItem>0) {
            selection->firstVisibleItem--;
            changed=1;
        }
        break;
    case 0x80:
        if(selection->selectedItem<6 &&
           (selection->selectedItem+selection->firstVisibleItem<selection->cachedRowItemCounts[selection->activeRow]-1 ||
            selection->selectedItem+selection->firstVisibleItem<selection->cachedRowItemCounts[(selection->activeRow+1)%2]-1)) {
            selection->selectedItem++;
            changed=1;
        } else if(selection->firstVisibleItem<selection->maxFirstVisibleItem) {
            selection->firstVisibleItem++;
            changed=1;
        }
        if(selection->cachedRowItemCounts[selection->activeRow]<=selection->selectedItem+selection->firstVisibleItem)
            selection->activeRow=(selection->activeRow+1)%2;
        break;
    case 0x20:
        if(selection->activeRow>0 && selection->selectedItem+selection->firstVisibleItem<selection->cachedRowItemCounts[selection->activeRow-1]) {
            selection->activeRow--;
            changed=1;
        }
        break;
    case 0x10:
        if(selection->activeRow<1 && selection->selectedItem+selection->firstVisibleItem<selection->cachedRowItemCounts[selection->activeRow+1]) {
            selection->activeRow++;
            changed=1;
        }
        break;
    }
    item=data_ov005_0205b80c->firstItemSlot[selection->activeRow][selection->selectedItem+selection->firstVisibleItem];
    if(item && item->indicatorState==1)item->indicatorState=2;
    return changed;
}
