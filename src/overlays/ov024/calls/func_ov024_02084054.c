/* func_ov024_02084054 -- resolve the main BG3 screen base, ov024. Returns the fixed
 * LCDC mapping (0x06400000) when `direct` is set, else the live G2 BG3 screen pointer. */
extern void *G2_GetBG3ScrPtr(void);
void *func_ov024_02084054(int direct) {
    if (direct != 0) {
        return (void *)0x6400000;
    }
    return G2_GetBG3ScrPtr();
}
