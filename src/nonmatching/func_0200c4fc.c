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
        ok = func_020093e8(6, header | 0x10000 | 0x1000000, 0) >= 0;
    }
    if ((ok & 0xff) == 0) {
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

/* PARK 2026-07-19 (segunda pasada tras el censo): 256/256 bytes, UNA pareja de instrucciones:
 *
 *   ROM   cmp r0,#0 / movlt r0,#0 / movge r0,#1 / tst r0,#0xff / bne exito
 *   mwcc  cmp r0,#0 / movge r0,#1 / movlt r0,#0 / tst r0,#0xff / bne exito
 *
 * ★ EL `tst #0xff` YA ESTA RESUELTO. Salio del experimento del censo: buscar funciones YA CASADAS
 * con `tst rX,#0xff` encontro `func_ov002_02053790`, y alli el `tst` viene de un `& 0xff`
 * EXPLICITO en la condicion, no de un tipo de ancho byte:
 *       if ((ok & 0xff) == 0) { ... }
 * (Con `unsigned char ok` mwcc mete un `and` de mas y sube a 260. Era la pista falsa.)
 *
 * Queda solo el orden de los dos `mov` condicionales. Probado: `>= 0`, `< 0 ? 0 : 1`, `!(< 0)`,
 * `ok=0; if(>=0) ok=1;`, `ok=1; if(<0) ok=0;`, el `&&` entero, y el ternario anidado. mwcc
 * normaliza todas a movge-primero. */
