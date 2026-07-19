extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void func_02001f10(void *queue);
extern char data_027e0000;
extern char data_027e006c;

/* Blocks until one of the requested IRQs has been serviced. */
void OS_WaitIrq(int clear, unsigned int mask) {
    int enabled = OS_DisableInterrupts();
    if (clear != 0) {
        *(unsigned int *)((char *)&data_027e0000 + 0x3ff8) &= ~mask;
    }
    OS_RestoreInterrupts(enabled);
    if ((mask & *(unsigned int *)((char *)&data_027e0000 + 0x3ff8)) == 0) {
        unsigned int *checked = (unsigned int *)((char *)&data_027e0000 + 0x3ff8);
        do {
            func_02001f10(&data_027e006c);
        } while ((mask & *checked) == 0);
    }
}

/* PARK 2026-07-19: 116/116 bytes, MISMAS instrucciones, solo planificacion: mwcc calcula el
 * puntero del bucle (`add r0,base,#0x3f8` + `add r6,r0,#0x3c00`) ANTES del `tst`+`popne` de salida
 * rapida; el ROM lo hace despues. Probado: `while` normal, `if`+`do/while`, `if`+return temprano
 * (sale 4 bytes largo) y el puntero del bucle como variable local. Todo lo demas casa, incluida la
 * curiosidad de que el ROM descompone el MISMO offset 0x3ff8 de dos maneras distintas
 * (`+0x3000` y luego `[..,#0xff8]` en la primera lectura; `+0x3f8` y luego `+0x3c00` en el bucle),
 * lo que reproduce mwcc sin ayuda. */
