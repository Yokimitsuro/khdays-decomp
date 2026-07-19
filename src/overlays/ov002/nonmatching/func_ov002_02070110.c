extern int func_ov002_0207285c(int slot);
extern char *NNSi_FndAllocFromDefaultExpHeap(int size);
extern void func_ov002_0206ffa4(void);
extern char data_0204c240;

static inline void Ov002_SetSlot(void **slot, void *value) {
    if (value != (void *)-1) {
        *slot = value;
    }
}

/* Allocates a script-callback record: resolves the model id (-1 = no slot, -2 = unresolved),
 * stores the caller's tag in the half the flags select, and fills the three handler slots. */
char *func_ov002_02070110(int kind, int tag, int slot, void *ctx) {
    char *rec = NNSi_FndAllocFromDefaultExpHeap(0x18);
    int id;
    rec[0x14] = (char)kind;
    if (slot >= 0) {
        id = func_ov002_0207285c(slot);
        if (id < 0) {
            rec[0x15] = (char)~1;
        } else {
            rec[0x15] = (char)id;
        }
    } else {
        rec[0x15] = (char)~0;
    }
    *(short *)(rec + 0x16) = (*(unsigned char *)&data_0204c240 & 4) != 0
        ? (short)(tag >> 0x10) : (short)(unsigned short)tag;
    *(void **)(rec + 0xc) = ctx;
    Ov002_SetSlot((void **)rec, (void *)&func_ov002_0206ffa4);
    Ov002_SetSlot((void **)(rec + 4), 0);
    Ov002_SetSlot((void **)(rec + 8), 0);
    return rec;
}

/* PARK 2026-07-19: 124/124 bytes. El bloque del ternario y las tres comprobaciones de centinela
 * CASAN; sobra un `lsls`+`asrs` (la conversion a `short` del resultado del ternario) justo antes
 * del `strh`, y falta otro par de instrucciones mas adelante que compensa el tamaño.
 *
 * ★ LO QUE SI SE RESOLVIO, y es reutilizable: las tres comparaciones contra -1 con valores
 * CONSTANTES (`if (v != -1) *slot = v;`) las pliega mwcc si se escriben abiertas -- se pierden 12
 * bytes. Con un helper `static inline` sobreviven:
 *     static inline void Ov002_SetSlot(void **slot, void *value) {
 *         if (value != (void *)-1) { *slot = value; }
 *     }
 * Es el mismo truco del bool materializado, aplicado a una COMPARACION que el compilador podria
 * decidir en tiempo de compilacion. Sin el helper la funcion sale de 112 en vez de 124.
 *
 * Falta: quitar la conversion sobrante sin perder los otros 4 bytes. Probado `(short)` en cada
 * rama, sin casts, y con una variable `int v` intermedia (las dos ultimas dan 120). */
