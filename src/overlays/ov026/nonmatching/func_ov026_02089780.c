extern char *data_ov026_02091368;
extern int func_ov026_02085d7c(int handle, int kind, int a, int x, int y);
extern int func_ov026_0208427c(void *p, int id);
extern int func_ov026_02084374(void *p, int cell);
extern void func_ov026_02084330(void *p, int cell, int value);
extern void func_ov026_02084488(void *p, int cell, int flag);

/* Creates the four rows of the stats tab (label + value cell per row, 16 pixels apart) and starts
 * the panel's slide-in animation. */
void func_ov026_02089780(void) {
    char *snd;
    int cell;
    int *rows;
    int handle;
    int i;
    char *st = *(char **)&data_ov026_02091368;
    snd = st + 0x530;
    rows = (int *)(st + 0xc4f4);
    handle = *(int *)(st + 0xbfb4);
    for (i = 0; i < 4; i++) {
        int top = (i + 1) << 4;
        rows[i + 1] = func_ov026_02085d7c(handle, 0, *(short *)(st + 0xe),
                                          0x30000, (top + 0x20) << 0xc);
        rows[i + 5] = func_ov026_02085d7c(handle, 8, 1, 0x25000, (top + 0x24) << 0xc);
    }
    cell = func_ov026_0208427c(snd + 0x7000, 6);
    func_ov026_02084330(snd + 0x7000, cell, func_ov026_02084374(snd + 0x7000, cell));
    func_ov026_02084488(snd + 0x7000, cell, 0);
}

/* PARK 2026-07-19: 212/212 bytes, mismas instrucciones, DOS registros permutados:
 *   ROM   r5 = el cero hoisteado (que luego es `cell`) / r4 = snd
 *   mwcc  r4 = el cero                                  / r5 = snd
 * (st->sb, i->r8, rows->r6, handle->r7 SI casan, y eso costo llegar a este orden de declaracion.)
 *
 * Probadas SEIS formas: cuatro ordenes de declaracion, mover la asignacion de `snd` detras de
 * `rows`/`handle`, y escribir el cero como `int cell = 0;` pasado de argumento (por si era el
 * artefacto de copia `mov r5,r8`). La pareja no se mueve. Clase bloqueada.
 *
 * ★ LO QUE SI SE ARREGLO por el camino (16 bytes) y esta documentado: la direccion `st + 0x7530`
 * hay que escribirla con el SPLIT EXPLICITO -- `char *snd = st + 0x530;` y luego `snd + 0x7000`
 * en los cuatro usos. Escrita entera, mwcc recalcula los dos `add` en cada uso (8 instrucciones);
 * con el split hoistea la parte baja en un registro y solo repite el `add #0x7000` como el ROM. */
