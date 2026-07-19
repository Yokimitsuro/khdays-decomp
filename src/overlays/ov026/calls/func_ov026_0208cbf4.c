extern char *data_ov026_02091368;
extern int func_ov026_0208e40c(void);
extern void func_ov026_0208a774(void);
extern void func_ov026_0208a658(void);
extern void func_ov026_0208c5d8(void);
extern void func_ov026_0208b0bc(void);

/* Commits the pending selection: on success hands over to the confirm screen, otherwise rewinds to
 * the list and flags it dirty. */
void *func_ov026_0208cbf4(void) {
    char *st = *(char **)&data_ov026_02091368 + 0xc54c;
    *(int *)(st + 0x24) = func_ov026_0208e40c();
    func_ov026_0208a774();
    *(int *)(st + 0x20) = 0;
    if (*(int *)(st + 0x24) != 0) {
        return (void *)&func_ov026_0208c5d8;
    }
    func_ov026_0208a658();
    *(int *)(*(char **)&data_ov026_02091368 + 0xc3d4) = 1;
    return (void *)&func_ov026_0208b0bc;
}
