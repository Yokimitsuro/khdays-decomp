/* Shows or hides the whole save-page object group: the ten ids in the table
 * plus the fixed id 7, either all visible (mode 1) or all hidden (mode 0).
 * Any other mode leaves the page alone. The first parameter is the caller's
 * own object and is dead here: the list comes from the shared context. */
typedef unsigned short u16;

typedef struct {
    int ids[10];
} EntryIdGroup10;

extern EntryIdGroup10 data_ov025_020b3e20;
extern int func_ov025_02084a50(void);
extern int func_ov025_020894b0(int list, int id);
extern void func_ov025_0208962c(int list, int entry, int visible);

void func_ov025_02090000(int self, int mode) {
    int list = func_ov025_02084a50();
    EntryIdGroup10 group = data_ov025_020b3e20;
    unsigned int i;
    int entry;

    switch (mode) {
    case 0:
        for (i = 0; i < 10; i++) {
            entry = func_ov025_020894b0(list, (u16)group.ids[i]);
            func_ov025_0208962c(list, entry, 0);
        }
        entry = func_ov025_020894b0(list, 7);
        func_ov025_0208962c(list, entry, 0);
        break;
    case 1:
        for (i = 0; i < 10; i++) {
            entry = func_ov025_020894b0(list, (u16)group.ids[i]);
            func_ov025_0208962c(list, entry, 1);
        }
        entry = func_ov025_020894b0(list, 7);
        func_ov025_0208962c(list, entry, 1);
        break;
    }
}
