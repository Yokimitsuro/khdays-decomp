/* ov002 help entries, 0x0207e98c-0x0207e9c4.
 *
 * Two seven-word records, each holding four counters, a pointer to its row block and
 * the handler that draws it.
 */

typedef void (*Ov002HelpFn)(void);

typedef struct {
    int nIndex;
    int nId;
    int nRows;
    int nFlags;
    void *pRows;
    int nStep;
    Ov002HelpFn pfnDraw;
} Ov002HelpEntry;

extern int data_ov002_0207dd84;
extern int data_ov002_0207dd8c;
extern void func_ov002_0205779c(void);
extern void func_ov002_02057888(void);

Ov002HelpEntry data_ov002_0207e98c[2] = {
    { 1, 77, 6, 0, &data_ov002_0207dd8c, 8, func_ov002_0205779c },
    { 0, 46, 4, 2, &data_ov002_0207dd84, 2, func_ov002_02057888 },
};
