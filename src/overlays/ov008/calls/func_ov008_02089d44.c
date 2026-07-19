extern char *data_ov008_02090fac;
extern int func_ov008_0208b55c(void);
extern void func_ov008_020878c4(void);
extern void func_ov008_020877a8(void);
extern void func_ov008_02089728(void);
extern void func_ov008_0208820c(void);

/* Commits the pending selection: on success hands over to the confirm screen, otherwise rewinds to
 * the list and flags it dirty. */
void *func_ov008_02089d44(void) {
    char *st = *(char **)&data_ov008_02090fac + 0xc54c;
    *(int *)(st + 0x24) = func_ov008_0208b55c();
    func_ov008_020878c4();
    *(int *)(st + 0x20) = 0;
    if (*(int *)(st + 0x24) != 0) {
        return (void *)&func_ov008_02089728;
    }
    func_ov008_020877a8();
    *(int *)(*(char **)&data_ov008_02090fac + 0xc3d4) = 1;
    return (void *)&func_ov008_0208820c;
}
