/* NONMATCHING: semantics correct, CSE/alias-conservatism tie (1 instruction).
 * The ROM reloads the block pointer from the global (data_0205ac2c[2]) before EACH
 * of the param_3 and param_2 field stores (`ldr r2,[r1,#8]` each). mwcc 3.0/139
 * proves the heap block cannot alias the global and CSEs the reload, so it keeps
 * the pointer in a register for the param_2 store (-4B). `volatile` on the global
 * over-corrects (also splits the two OS_CreateThread arg reads, +8B); block-local
 * vs all-global only shifts which stores reload. No form reproduces the ROM's
 * exact per-store reload. Whole family (ov000_020549fc + byte-identical twins) ties.
 *
 * Spawn the ov000 worker thread: allocate a 0x2d0-byte block (OSThread + stack +
 * context), stash it in the global, record param_1/param_3/param_2 in the context
 * at +0x2c0/+0x2c4/+0x2c8, then OS_CreateThread (entry func_ov000_0205496c,
 * arg=block, stackTop=block+0x2c0, size 0x200, prio 0x11) and wake it. *
 * DIAGNOSTICO PRECISADO (2026-07-19, con tools/poolmap.py): el residuo es que **el ROM RECARGA
 * `data_ov000_0205ac2c[2]` antes de cada uso** (`ldr r2,[r1,#8]` tres veces) y mwcc lo mantiene
 * en un registro. El primer uso tras la asignacion SI va directo en los dos.
 *   sin el local, todo por el global .......... size -4 (mwcc sigue haciendo CSE)
 *   `volatile` en el global ................... size +4 y **cambia toda la asignacion de
 *                                               registros** (mete r7 en el push): eje equivocado
 *   local + `volatile` ........................ size +4, igual
 * Falta encontrar que hace que mwcc no pueda cachear el global. No es el local ni volatile. */
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void OS_CreateThread(void *thread, void *func, void *arg, void *stackTop, unsigned int stackSize, unsigned int prio);
extern void OS_WakeupThreadDirect(void *thread);
extern void func_ov000_0205496c(void);
extern int data_ov000_0205ac2c[];
void func_ov000_020549fc(int param_1, int param_2, int param_3) {
    int block = (int)NNSi_FndAllocFromDefaultExpHeap(0x2d0);
    data_ov000_0205ac2c[2] = block;
    *(int *)(block + 0x2c0) = param_1;
    *(int *)(data_ov000_0205ac2c[2] + 0x2c4) = param_3;
    *(int *)(data_ov000_0205ac2c[2] + 0x2c8) = param_2;
    OS_CreateThread((void *)data_ov000_0205ac2c[2], (void *)func_ov000_0205496c,
                    (void *)data_ov000_0205ac2c[2], (void *)(data_ov000_0205ac2c[2] + 0x2c0),
                    0x200, 0x11);
    OS_WakeupThreadDirect((void *)data_ov000_0205ac2c[2]);
}
