/* Shows or hides the whole save-page object group: the ten ids in the table
 * plus the fixed id 7, either all visible (mode 1) or all hidden (mode 0).
 * Any other mode leaves the page alone. The first parameter is the caller's
 * own object and is dead here: the list comes from the shared context. */
typedef unsigned short u16;

typedef struct {
    int ids[10];
} EntryIdGroup10;

extern EntryIdGroup10 data_ov008_0208f2c0;
extern int func_ov008_02050c28(void);
extern int func_ov008_02055808(int list, int id);
extern void func_ov008_02055a1c(int list, int entry, int visible);

void func_ov008_0205da8c(int self, int mode) {
    int list = func_ov008_02050c28();
    EntryIdGroup10 group = data_ov008_0208f2c0;
    unsigned int i;
    int entry;

    switch (mode) {
    case 0:
        for (i = 0; i < 10; i++) {
            entry = func_ov008_02055808(list, (u16)group.ids[i]);
            func_ov008_02055a1c(list, entry, 0);
        }
        entry = func_ov008_02055808(list, 7);
        func_ov008_02055a1c(list, entry, 0);
        break;
    case 1:
        for (i = 0; i < 10; i++) {
            entry = func_ov008_02055808(list, (u16)group.ids[i]);
            func_ov008_02055a1c(list, entry, 1);
        }
        entry = func_ov008_02055808(list, 7);
        func_ov008_02055a1c(list, entry, 1);
        break;
    }
}
