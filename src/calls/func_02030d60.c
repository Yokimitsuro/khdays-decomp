/* Runs every entry of the current effect list (data_0204c22c): with the list's +0x6c request clear
 * the +0x68 state resets; inside the effect arena (data_0204c02c, func_0202362c) each of the +8
 * entries (+4 array, 12 bytes each) is stepped by func_02030a4c; the request is then consumed. */
typedef struct {
    char data[0xc];
} EffectEntry;

typedef struct {
    int pad00;
    EffectEntry *entries;   /* 0x04 */
    int count;              /* 0x08 */
    char pad0c[0x68 - 0xc];
    int state;              /* 0x68 */
    int request;            /* 0x6c */
} EffectList;

extern EffectList *data_0204c22c;
extern int data_0204c02c;
extern int func_0202362c(int arena);
extern void func_02030a4c(EffectEntry *entry);

void func_02030d60(void)
{
    EffectList *list = data_0204c22c;
    int i;
    int old;

    if (list == 0) {
        return;
    }
    if (list->request == 0) {
        list->state = 0;
    }
    old = func_0202362c(data_0204c02c);
    for (i = 0; i < list->count; i++) {
        func_02030a4c(&list->entries[i]);
    }
    list->request = 0;
    func_0202362c(old);
}
