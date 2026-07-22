/* Stores the two words at the head of the GFX command context (data_02047370) and
 * tail-calls func_020114e4 with the context address.
 *
 * Same literal-pool subtlety as func_020115b8: the ROM's pool holds 0x02047370 twice,
 * and mwcc emits two entries only for two DISTINCT symbols, hence the
 * data_02047370_budget alias for the second reference. */
extern char data_02047370;
extern char data_02047370_budget;
extern void *func_020114e4();

void *func_02011594(int a, int b) {
    int *ctx = (int *)&data_02047370;
    ctx[0] = a;
    ctx[1] = b;
    return func_020114e4(&data_02047370_budget);
}
