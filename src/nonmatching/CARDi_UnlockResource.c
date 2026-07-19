extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void func_02001f10(void *queue);
extern void OS_WakeupThread(void *queue);
extern void OS_Terminate(void);
extern char data_020464e0;


/* Releases one level of the card bus lock; the last level hands it to the next waiter. */
void CARDi_UnlockResource(int owner, int kind) {
    char *card = (char *)&data_020464e0;
    int enabled = OS_DisableInterrupts();
    if (*(int *)(card + 8) != owner || *(int *)(card + 0xc) == 0) {
        OS_Terminate();
    } else {
        if (*(int *)(card + 0x18) != kind) {
            OS_Terminate();
        }
        *(int *)(card + 0xc) = *(int *)(card + 0xc) - 1;
        if (*(int *)(card + 0xc) == 0) {
            *(int *)(card + 8) = ~2;
            *(int *)(card + 0x18) = 0;
            OS_WakeupThread(card + 0x10);
        }
    }
    **(int **)card = 0;
    OS_RestoreInterrupts(enabled);
}

/* PARK 2026-07-19: 140/140 bytes, mismas instrucciones, PLANIFICACION:
 *   ROM   mvn r2,#2 / mov r1,#0 / add r0,r4,#0x10 / str r2,[r4,#8] / str r1,[r4,#0x18]
 *   mwcc  mvn r0,#2 / str r0,[r4,#8] / mov r1,#0 / add r0,r4,#0x10 / str r1,[r4,#0x18]
 * El ROM agrupa las dos constantes y el argumento de la llamada antes de los dos `str`; mwcc
 * intercala. Probado: los dos ordenes de almacenamiento y las constantes como locales (eso hace
 * que derive el -3 con `sub r1,r0,#3`, peor). El resto casa, incluido el `||` de la comprobacion
 * doble que comparte el mismo `OS_Terminate()`. */
