/* func_ov008_020837f8 -- ov026 layout pass: release the two five-entry row bands at +0xc360
 * (entries 5..9 and 10..14), then re-window the panel at +0xc160 twice (the small 0x50x0x18 box
 * at 0x60,0x70 first, then the full-width 0xa0-tall strip) and refresh item 0x3f of the widget
 * table at +0x2ab0.
 *
 * Two source-order facts decide the whole register assignment, and neither is a tie:
 *  - the declaration order below (st, rows, handle, i, panel) is the one that colours them as the
 *    ROM does; tools/declperm.py finds it (4 of the 120 orders reach 4 bytes, this is one).
 *  - `rows` must be computed BEFORE `handle`: both need mwcc to split a >4095 offset into an
 *    `add #0xN000` temporary, and the two temporaries get r0/r1 in source order. */
extern char *data_ov008_02090fac;
extern void func_02032450(int handle, int cell);
extern void func_0203011c(void *p, int a, int b, int c, int d);
extern int func_ov008_02054788(void *p, int id);
extern void func_ov008_02054ba4(void *p, int cell, int on);

/* Refreshes the five detail rows and re-lays out both panels, then silences the hover sound. */
void func_ov008_020837f8(void) {
    char *st;
    int *rows;
    int handle;
    int i;
    char *panel;
    st = *(char **)&data_ov008_02090fac;
    rows = (int *)(st + 0xc360);
    handle = *(int *)(st + 0xbfb0);
    panel = st + 0xc160;
    for (i = 0; i < 5; i++) {
        func_02032450(handle, rows[i + 5]);
        func_02032450(handle, rows[i + 10]);
    }
    func_0203011c(panel, 0x50, 0x18, 0x60, 0x70);
    func_0203011c(*(char **)&data_ov008_02090fac + 0xc160, 0, 0xa0, 0x100, 0x20);
    func_ov008_02054ba4(*(char **)&data_ov008_02090fac + 0x2ab0,
                        func_ov008_02054788(*(char **)&data_ov008_02090fac + 0x2ab0, 0x3f), 0);
}

/* PARK 2026-07-19: 208/208 bytes, mismas instrucciones, ROTACION de tres registros:
 *   ROM   r4=handle r5=i r6=panel r7=rows
 *   mwcc  r4=i r5=panel r6=handle r7=rows
 * Probados SEIS ordenes de declaracion distintos; la rotacion no se mueve (el reparto no lo decide
 * aqui el orden de declaracion sino la estructura del bucle). Clase bloqueada.
 *
 * ★ LO QUE SI SE ARREGLO por el camino, y vale para otras: mwcc hacia CSE de `rows + i*4` en un
 * registro callee-saved EXTRA (r8) y lo mantenia vivo sobre la llamada, mientras que el ROM
 * recalcula `add r0, r7, r5, lsl #2` antes de cada una de las dos cargas. Escrito como
 *     *(int *)(rows + i * sizeof(int) + 0x14)   -> CSE, +4 bytes y un registro de mas
 *     rows[i + 5]  /  rows[i + 10]              -> recalcula, exacto
 * O sea: con `base + i*N + K` mwcc ve la subexpresion comun; con INDICE DE ARRAY y el
 * desplazamiento metido en el indice, no. Ver codegen-cracks.md. */
