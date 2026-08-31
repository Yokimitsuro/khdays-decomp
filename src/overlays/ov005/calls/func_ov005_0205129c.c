typedef unsigned char u8;
typedef unsigned short u16;
typedef struct InventoryView {
    char opaque0[0x810];
    u8 firstItemCount;
    char opaque811[0xee0-0x811];
    u16 equippedItems[3][40];
} InventoryView;
extern InventoryView *data_0204be18;
void func_ov005_0205129c(unsigned int itemId, int quantity) {
    int removed=0;
    int row,slot;
    for (row=2;row>=0;row--) {
        for (slot=39;slot>=0;slot--) {
            if (data_0204be18->equippedItems[row][slot]==itemId) {
                if (quantity<=0) goto done;
                data_0204be18->equippedItems[row][slot]=0;
                removed++;
                quantity--;
            }
        }
    }
done:
    {
        u8 *counts=&data_0204be18->firstItemCount;
        int count=counts[itemId];
        counts[itemId]=count>removed?count-removed:0;
    }
}
