/* Look an entry up in the chain and, when asked to, copy its box into the layout context.
 *
 * The entry keeps its origin at +8 and +0xa and its size at +0xc and +0xe; the layout keeps the
 * origin the same way round but the size crossed, width at +6 and height at +4, which is why the
 * two middle copies read as swapped. The cell size at +0x10 comes across unchanged.
 *
 * The entry pointer is the return value, on both paths, which is what keeps it in r0 untouched
 * to the end and leaves r1 as the temporary for every copy.
 *
 * Ghidra carries the destination as Ov002LayoutContext.
 */

typedef unsigned short u16;

typedef struct {
    u16 wOriginX;               /* +0x00 */
    u16 wOriginY;               /* +0x02 */
    u16 wHeight;                /* +0x04 */
    u16 wWidth;                 /* +0x06 */
    char pad0008[8];
    int nCellSize;              /* +0x10 */
} Ov002LayoutContext;

extern char *func_ov002_0206480c(int *list, unsigned int id);
extern Ov002LayoutContext *data_ov002_0207f638;

char *func_ov002_02064a30(int *list, unsigned int id, int copy) {
    Ov002LayoutContext *layout = data_ov002_0207f638;
    char *entry = func_ov002_0206480c(list, id);

    if (copy != 0) {
        layout->wOriginX = *(u16 *)(entry + 0x08);
        layout->wOriginY = *(u16 *)(entry + 0x0a);
        layout->wWidth = *(u16 *)(entry + 0x0c);
        layout->wHeight = *(u16 *)(entry + 0x0e);
        layout->nCellSize = *(int *)(entry + 0x10);
    }
    return entry;
}
