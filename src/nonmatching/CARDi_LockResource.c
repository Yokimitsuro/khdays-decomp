extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void func_02001f10(void *queue);
extern void OS_WakeupThread(void *queue);
extern void OS_Terminate(void);
extern char data_020464e0;


/* Takes the card bus for one owner/kind pair, blocking until it is free. Re-locking with a
 * different kind is a fatal error. */
void CARDi_LockResource(int owner, int kind) {
    char *card = (char *)&data_020464e0;
    int free;
    int enabled = OS_DisableInterrupts();
    free = ~2;
    if (*(int *)(card + 8) == owner) {
        if (*(int *)(card + 0x18) != kind) {
            OS_Terminate();
        }
    } else {
        goto test;
    wait:
        func_02001f10(card + 0x10);
    test:
        if (*(int *)(card + 8) != free) {
            goto wait;
        }
        *(int *)(card + 8) = owner;
        *(int *)(card + 0x18) = kind;
    }
    *(int *)(card + 0xc) = *(int *)(card + 0xc) + 1;
    **(int **)card = 0;
    OS_RestoreInterrupts(enabled);
}

/* PARK 2026-07-19: 132/132 bytes, mismas instrucciones, ROTACION de tres registros:
 *   ROM   r4=card  r5=enabled  r6=marcador(-3)
 *   mwcc  r5=card  r6=enabled  r4=marcador
 * Clase bloqueada. Probado: el -3 como literal `~2` en la condicion, como local declarada antes y
 * despues de `enabled`, y como local asignada por separado. El resto casa entero, incluida la
 * forma del bucle con `goto` explicito (el ROM prueba la condicion UNA vez, ver codegen-cracks). */
