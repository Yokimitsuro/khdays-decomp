/* func_ov107_020c9b68 -- resolve a message handler by id: fast array lookup in the
 * singleton manager's table when present and id is in range, otherwise fall back
 * to a linear scan of its handler list (same list-walk idiom as func_ov107_020c2b50). */
typedef unsigned short u16;
typedef unsigned int u32;

extern int func_01fffd70(void *list);
extern int func_01fffd8c(void *list);

struct HandlerMgr {
    u32 field_00;
    u32 list_04;        /* address-taken list container */
    char pad_08[0x1c];
    u32 count;           /* +0x24 */
    char pad_28[0x20];
    int *table;           /* +0x48 */
};

extern struct HandlerMgr *data_ov107_020cbf1c;

int func_ov107_020c9b68(unsigned int id)
{
    struct HandlerMgr *mgr = data_ov107_020cbf1c;
    int node, e;

    if (mgr->table != 0 && id < (u16)mgr->count) {
        return mgr->table[id];
    }
    node = func_01fffd70(&mgr->list_04);
    while (node != 0) {
        e = *(int *)node;
        if (*(u16 *)(e + 2) == id) {
            return e;
        }
        node = func_01fffd8c(&mgr->list_04);
    }
    return 0;
}
