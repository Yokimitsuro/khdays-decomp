extern char *data_ov026_02091368;
extern void func_ov026_020866a8(void);
extern void func_ov026_0208a774(void);
extern int func_ov026_0208e40c(void);
extern void func_ov026_0208c5d8(void);
extern void func_ov026_0208b0bc(void);

/* Confirms the current selection. Only tab 3 can produce a result worth going to the confirm
 * screen for; everything else falls back to the list. */
void *func_ov026_0208b04c(void) {
    char *st = *(char **)&data_ov026_02091368;
    int result;
    func_ov026_020866a8();
    func_ov026_0208a774();
    *(int *)(st + 0xc56c) = 1;
    if (*(int *)(st + 0xc250) == 3) {
        result = func_ov026_0208e40c();
        *(int *)(st + 0xc570) = result;
        if (result != 0) {
            *(int *)(st + 0xc568) = 1;
            return (void *)&func_ov026_0208c5d8;
        }
    }
    *(int *)(st + 0xc3d4) = 1;
    return (void *)&func_ov026_0208b0bc;
}
