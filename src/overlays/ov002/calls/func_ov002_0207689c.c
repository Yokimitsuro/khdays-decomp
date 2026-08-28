typedef signed char s8;

typedef struct {
    char pad00[4];
    char *pContext;                 /* +0x04 */
} Ov002SceneRef;

extern Ov002SceneRef data_ov002_0207fa20;

/* One eight byte row per panel id: the overlay that panel needs and the entry
 * point inside it.  The two halves are reached through their own literal pool
 * words, which is why the tree carries two symbols for one table. */
extern int data_ov002_0207f58c[];
extern int data_ov002_0207f590[];

extern void func_0201e4a8(int nKind, int nHandle);
extern void func_0201e470(int nKind, int nHandle);
extern void func_02020aa8(int nId, int nFlags);

/* Give the scene the sub-overlay a panel id asks for.
 *
 * Whatever was loaded is unloaded first and its handle marked empty.  The new
 * id is recorded even when its row carries no overlay, so a panel that brings
 * nothing still becomes the current one.  Counterpart of the teardown at
 * func_ov002_02076170, which unloads and clears the same two fields.
 */
void func_ov002_0207689c(int nPanelId)
{
    char *pContext = data_ov002_0207fa20.pContext;

    if (*(s8 *)(pContext + 0x260) != -1) {
        func_0201e4a8(0, *(int *)(pContext + 0x264));
        *(int *)(data_ov002_0207fa20.pContext + 0x264) = -1;
    }

    *(s8 *)(data_ov002_0207fa20.pContext + 0x260) = (s8)nPanelId;

    if (data_ov002_0207f58c[nPanelId * 2] != -1) {
        *(int *)(data_ov002_0207fa20.pContext + 0x264) = data_ov002_0207f58c[nPanelId * 2];
        func_0201e470(0, *(int *)(data_ov002_0207fa20.pContext + 0x264));
        func_02020aa8(nPanelId + 5, data_ov002_0207f590[nPanelId * 2]);
    }
}
