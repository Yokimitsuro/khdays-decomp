/* Whether the menu grid built from the save block's +0xee0 id rows holds an entry of kind 4
 * (the +0x18 word of the entry the node's page/column/row point at); with a non-zero `min` the
 * node must also carry a +4 record and a +8 count of at least `min`. The grid context, entry
 * table and node list are built and torn down around the search. */
typedef unsigned short u16;

struct MenuNode {
    char pad000[4];
    int pRecord;            /* +0x04 */
    u16 nCount;             /* +0x08 */
    u16 nPage;              /* +0x0a */
    char pad00c[4];
    u16 nColumn;            /* +0x10 */
    u16 nRow;               /* +0x12 */
};

extern void NNS_FndInitList(void *list, int offset);
extern void func_ov069_020ba1c4(void *ctx, void **hooks);
extern void func_ov069_020ba4cc(void *ctx, void **entries, void *list, u16 *ids);
extern void func_ov069_020ba250(void *ctx, void **entries, void *list);
extern void *NNS_FndGetNextListObject(void *list, void *cur);
extern void func_ov069_020ba71c(void *ctx, void **entries, void *list);
extern void WM_EndKeySharing_0x020ba244(void *ctx);
extern char *data_0204be18;

int func_ov069_020b83d8(unsigned int min)
{
    int found;
    int list[3];
    char *entries[3][0x28];
    char ctx[0x100];
    struct MenuNode *node;

    found = 0;
    NNS_FndInitList(list, 0x28);
    func_ov069_020ba1c4(ctx, 0);
    func_ov069_020ba4cc(ctx, (void **)entries, list, (u16 *)(data_0204be18 + 0xee0));
    func_ov069_020ba250(ctx, (void **)entries, list);
    for (node = NNS_FndGetNextListObject(list, 0); node != 0; node = NNS_FndGetNextListObject(list, node)) {
        if (*(int *)(entries[node->nPage][node->nColumn + node->nRow * 5] + 0x18) == 4 &&
            (min == 0 || (node->pRecord != 0 && node->nCount >= min))) {
            found = 1;
            break;
        }
    }
    func_ov069_020ba71c(ctx, (void **)entries, list);
    WM_EndKeySharing_0x020ba244(ctx);
    return found;
}
