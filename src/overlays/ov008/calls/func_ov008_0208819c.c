extern char *data_ov008_02090fac;
extern void func_ov008_020837f8(void);
extern void func_ov008_020878c4(void);
extern int func_ov008_0208b55c(void);
extern void func_ov008_02089728(void);
extern void func_ov008_0208820c(void);

/* Confirms the current selection. Only tab 3 can produce a result worth going to the confirm
 * screen for; everything else falls back to the list. */
void *func_ov008_0208819c(void) {
    char *st = *(char **)&data_ov008_02090fac;
    int result;
    func_ov008_020837f8();
    func_ov008_020878c4();
    *(int *)(st + 0xc56c) = 1;
    if (*(int *)(st + 0xc250) == 3) {
        result = func_ov008_0208b55c();
        *(int *)(st + 0xc570) = result;
        if (result != 0) {
            *(int *)(st + 0xc568) = 1;
            return (void *)&func_ov008_02089728;
        }
    }
    *(int *)(st + 0xc3d4) = 1;
    return (void *)&func_ov008_0208820c;
}
