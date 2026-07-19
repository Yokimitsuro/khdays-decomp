extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern int func_020093e8(int channel, int word, int flag);
extern char data_02046390;

/* Starts a multi-block card command: clears the per-block status words, then pushes the two
 * command words through the PXI FIFO. On failure it reports the error through the callback. */
void func_0200c4fc(int header, int param, char *blocks, unsigned int count) {
    char *ctx = (char *)&data_02046390;
    void (*callback)(int, int, int);
    int i;
    int enabled;
    int ok;
    *(char **)(ctx + 0x14) = blocks;
    *(short *)(ctx + 0x10) = 0;
    *(short *)(ctx + 0x12) = (short)param;
    *(short *)(ctx + 0x18) = (short)count;
    for (i = 0; i < count; i++) {
        *(short *)(*(char **)(ctx + 0x14) + i * sizeof(long long) + 4) = 0;
    }
    enabled = OS_DisableInterrupts();
    if (func_020093e8(6, (param & 0xff) | 0x100 | 0x2000000, 0) < 0) {
        ok = 0;
    } else {
        ok = func_020093e8(6, header | 0x10000 | 0x1000000, 0) < 0 ? 0 : 1;
    }
    if (ok == 0) {
        OS_RestoreInterrupts(enabled);
        *(unsigned short *)((char *)&data_02046390 + 0x38) |= 2;
        callback = *(void (**)(int, int, int))((char *)&data_02046390 + 4);
        if (callback == 0) {
            return;
        }
        callback(1, 4, 0);
        return;
    }
    *(unsigned short *)((char *)&data_02046390 + 0x3a) |= 2;
    *(unsigned short *)((char *)&data_02046390 + 0x38) &= ~2;
    OS_RestoreInterrupts(enabled);
}

/* PARK 2026-07-19: 256/256 bytes. Todo casa salvo DOS detalles del bool de exito:
 *
 *   ROM   cmp r0,#0 / movlt r0,#0 / movge r0,#1 / tst r0,#0xff / bne exito
 *   mwcc  cmp r0,#0 / movge r0,#1 / movlt r0,#0 / cmp r0,#0    / bne exito
 *
 * (orden de los dos `mov` condicionales, y `tst #0xff` en vez de `cmp #0` -- lo segundo dice que
 * en el fuente el bool es de ANCHO BYTE, pero declararlo `unsigned char` mete un enmascarado y
 * sube a 260.)
 *
 * Tabla de lo probado (metodo de la iteracion 355):
 *   forma                                          | tamaño | notas
 *   `ok = A >= 0 && B >= 0;`                        | 256 ✓  | falta el `movlt` de la rama corta
 *   `if (A<0) ok=0; else ok = B>=0;`                | 256 ✓  | ESTA -- solo el orden de los mov
 *   idem con `B < 0 ? 0 : 1`                        | 256 ✓  | igual
 *   `unsigned char ok`                              | 260 ✗  | añade `and r0,#0xff`
 *   helper `static inline` que devuelve el bool     | 268 ✗  | mucho peor
 *   sin variable, `if (!(A && B))`                  | 240 ✗  | mwcc colapsa el bool entero
 *
 * LO QUE SI SE ARREGLO por el camino y vale para otras: el indice del bucle tiene que ser `int i`,
 * no `unsigned int i`. Con `unsigned` mwcc crea una induccion en BYTES aparte
 * (`mov r2,lr` + `add r2,r2,#8`) aunque uses `i * sizeof(long long)`; con `int` emite
 * `add r0,r0,lr,lsl #3` como el ROM. El truco de `sizeof` NO basta por si solo si el indice es
 * unsigned -- eso no estaba en el catalogo. */
