extern int func_ov002_0207285c(int slot);
extern void func_ov002_02077df0(void *node);
extern char data_ov002_0207fa28;

/* Ticks every queued object of every live spawn slot whose kind is below 6. */
void func_ov002_02078f60(void) {
    int i;
    int off = 0;
    char *node;
    char *next;
    for (i = 0; i < 0x18; i++) {
        if (func_ov002_0207285c(i) >= 0) {
            node = *(char **)(*(char **)((char *)&data_ov002_0207fa28 + 4) + off + 0xc4);
            while (node != 0) {
                next = *(char **)node;
                if (*(unsigned char *)(node + 0x2c) < 6) {
                    func_ov002_02077df0(node);
                }
                node = next;
            }
        }
        off += 0x184;
    }
}

/* PARK 2026-07-19: 72/72 bytes, rotacion de tres registros (i / off / next). Probados cuatro
 * ordenes de declaracion. Es la hermana de `func_ov002_02076534`, que SI caso -- alli el indice
 * era de stride 4 y bastaba con escribirlo como indice de array; aqui el stride es 0x184 y esa via
 * no existe sin inventar una struct de ese tamaño. Clase bloqueada. */
