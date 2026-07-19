extern char *data_ov026_02091368;
extern int func_02024da4(void *events);

/* Polls the touch queue for a press-and-hold and tracks the drag: on the first frame it snapshots
 * the anchor, afterwards it just follows the finger. */
void func_ov026_02085aa4(void) {
    char *st = *(char **)&data_ov026_02091368;
    unsigned short *touch = 0;
    char events[0x20];
    char *ui;
    char *pos;
    int i;
    unsigned short *e;
    for (i = func_02024da4(events) - 1; i >= 0; i--) {
        e = (unsigned short *)(events + i * sizeof(long long));
        if (e[2] == 1 && e[3] == 0) {
            touch = e;
            break;
        }
    }
    ui = st + 0xc000;
    if (touch != 0) {
        if (*(int *)(ui + 0x118) != 0) {
            *(int *)(ui + 0x118) = 0;
            *(int *)(ui + 0x11c) = 1;
            pos = st + 0xc100;
            *(unsigned short *)(pos + 0x28) = *(unsigned short *)(pos + 0x20);
            *(unsigned short *)(pos + 0x2a) = *(unsigned short *)(pos + 0x22);
            *(unsigned short *)(pos + 0x2c) = *(unsigned short *)(pos + 0x24);
            *(unsigned short *)(pos + 0x2e) = *(unsigned short *)(pos + 0x26);
        } else if (*(int *)(ui + 0x11c) == 0) {
            *(int *)(ui + 0x118) = 1;
        }
    } else {
        *(int *)(ui + 0x118) = 0;
        *(int *)(ui + 0x11c) = 0;
    }
    ui = st + 0xc000;
    if (*(int *)(ui + 0x118) == 0 && *(int *)(ui + 0x11c) == 0) {
        return;
    }
    pos = st + 0xc100;
    *(unsigned short *)(pos + 0x20) = touch[0];
    *(unsigned short *)(pos + 0x22) = touch[1];
}

/* PARK 2026-07-19: 248/248 bytes, instruccion por instruccion identico salvo DOS registros de
 * scratch permutados en el bucle:
 *
 *   ROM   add r2, sp, #0  (base fuera del bucle) / add r1, r2, r3, lsl #3  (elemento)
 *   mwcc  add r1, sp, #0                          / add r2, r1, r3, lsl #3
 *
 * Clase "el ROM se salta el registro libre mas bajo" (deferred-ties). Probado: `e` declarada
 * dentro y fuera del bucle, antes y despues de `i`, `events` como char[0x20] y como long long[4],
 * `&events[i]` y `events + i*sizeof(long long)`. Todo da el mismo par.
 * El resto casa entero, incluida la cadena if/else-if invertida (el `beq` del ROM va al caso
 * "sin toque", que por tanto es el ULTIMO bloque del fuente). */
