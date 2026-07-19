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
    int more;
    int src;
    int dst;
    void (*callback)(void *);
    void *arg;
    int enabled;
    MI_StopDma(*(int *)(card + 0x28));
    card = (char *)&data_020464e0;
    src = *(int *)(card + 0x1c);
    dst = *(int *)(card + 0x20);
    more = (*(int *)(card + 0x24) -= 0x200) != 0;
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

/* PARK 2026-07-19: 208/208 bytes, MISMAS instrucciones, UNA de posicion:
 *
 *   ROM   ldr r0,[0x24] / ldr r2,[0x1c] / ldr r1,[0x20] / subs r0,#0x200 / ...
 *   mwcc  ldr r0,[0x24] / ldr r1,[0x1c] / subs r0,#0x200 / ldr r2,[0x20] / ...
 *
 * mwcc mete el `subs` en el hueco de carga-uso; el ROM agrupa las TRES lecturas antes.
 * Probado (5 formas):
 *  - las tres lecturas a locales antes de restar -> pierde la materializacion del bool
 *    (`movne/moveq/cmp`) porque los `add` no tocan flags y mwcc salta directo: sale 196, -12 B.
 *  - `src`/`dst` a locales y `more = (campo -= 0x200) != 0` -> esta version, la mas cercana.
 *  - sumar el +0x200 al leer en vez de al guardar -> mueve el fallo, no lo quita.
 *  - intercambiar el orden de declaracion de `src` y `dst`.
 *  - `remaining` como local intermedia con el store explicito -> otra vez 196.
 *
 * El nudo es que el ROM quiere las dos cosas A LA VEZ: lecturas agrupadas Y el bool
 * materializado, y en mwcc cada una excluye a la otra. Sospecha para la proxima: un helper
 * `static inline` que devuelva el bool (ver codegen-cracks.md, "El bool materializado"), que es lo
 * que en otras funciones del SDK produce ese `movne/moveq/cmp` sin perder la planificacion. */
