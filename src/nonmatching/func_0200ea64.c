extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void MI_StopDma(unsigned int channel);
extern void OS_DisableIrqMask(unsigned int mask);
extern void OS_ResetRequestIrqMask(unsigned int mask);
extern int CARDi_ReadRomIDCore(void);
extern void CARDi_CheckPulledOutCore(int id);
extern void OS_WakeupThread(void *queue);
extern void OS_WakeupThreadDirect(void *thread);
extern void CARDi_SetCardDma(void);
extern char data_020464e0;


/* DMA completion handler for a card read: advances the transfer by one 512-byte page and either
 * kicks the next page or finishes the request and notifies the waiter. */
void func_0200ea64(void) {
    char *card = (char *)&data_020464e0;
    int len;
    int more;
    int src;
    int dst;
    void (*callback)(void *);
    void *arg;
    int enabled;
    MI_StopDma(*(int *)(card + 0x28));
    card = (char *)&data_020464e0;
    len = *(int *)(card + 0x24);
    src = *(int *)(card + 0x1c);
    dst = *(int *)(card + 0x20);
    more = (*(int *)(card + 0x24) = len - 0x200) != 0;
    *(int *)(card + 0x1c) = src + 0x200;
    *(int *)(card + 0x20) = dst + 0x200;
    if (more) {
        CARDi_SetCardDma();
        return;
    }
    OS_DisableIrqMask(0x80000);
    OS_ResetRequestIrqMask(0x80000);
    card = (char *)&data_020464e0;
    CARDi_CheckPulledOutCore(CARDi_ReadRomIDCore());
    **(int **)card = 0;
    callback = *(void (**)(void *))(card + 0x38);
    arg = *(void **)(card + 0x3c);
    enabled = OS_DisableInterrupts();
    *(int *)(card + 0x114) &= ~0x4c;
    OS_WakeupThread(card + 0x10c);
    if ((*(int *)(card + 0x114) & 0x10) != 0) {
        OS_WakeupThreadDirect(card + 0x44);
    }
    OS_RestoreInterrupts(enabled);
    if (callback == 0) {
        return;
    }
    callback(arg);
}

/* PARK 2026-07-19 (segunda pasada, MUCHO mas cerca): 208/208 bytes, mismas instrucciones, UNA
 * carga una posicion tarde:
 *
 *   ROM   ldr r0,[0x24] / ldr r2,[0x1c] / ldr r1,[0x20] / subs r0,#0x200 / str / movne / ...
 *   mwcc  ldr r0,[0x24] / ldr r1,[0x1c] / subs r0,#0x200 / ldr r2,[0x20] / movne / str / ...
 *
 * LO QUE SI SE RESOLVIO en esta pasada: el ROM quiere a la vez las lecturas agrupadas Y el bool
 * materializado (`movne/moveq/cmp`), y las formas obvias dan una cosa o la otra:
 *   - tres lecturas a locales y `more = len != 0`        -> agrupadas, SIN materializar (196 B)
 *   - `more = (campo -= 0x200) != 0`                     -> materializa, lecturas separadas
 *   - helper `static inline` que relee el campo          -> agrupadas, pero relee (204 B)
 *   - sin variables locales, todo con la expresion       -> `sub` en vez de `subs` (204 B)
 * ★ La que da LAS DOS: **la asignacion como expresion**
 *       more = (*(int *)(card + 0x24) = len - 0x200) != 0;
 *   con `len`/`src`/`dst` leidos antes. Eso es lo que hay abajo. Solo queda que mwcc mete el
 *   `subs` en el hueco de carga-uso de la tercera lectura.
 * Probado ademas: intercambiar el orden de lectura de src/dst, cuatro ordenes de declaracion, y
 * separar el decremento del store. Todos dejan la misma unica instruccion fuera de sitio. */
