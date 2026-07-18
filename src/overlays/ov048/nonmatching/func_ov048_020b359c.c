/* EQUIVALENT BUT NOT BYTE-EXACT -- 12 bytes (3 instrucciones), 2026-07-18.
 *
 * El ORDEN DE BLOQUES ya es correcto con la condicion NEGADA (`if (st != 0x30 && st != 0x31)`);
 * escribirla en positivo da 41 bytes, asi que esa parte esta resuelta y no hay que volver a
 * probarla.
 *
 * Lo que queda: el ROM usa **una salida unica** -- `bne <fin>` y `b <fin>` hacia un `pop`
 * compartido -- y mwcc duplica el epilogo con `popne` / `pop` en cada rama. Las tres
 * instrucciones que difieren son exactamente esas.
 *
 * Descartado (tools/bytedist.py):
 *   `else if` encadenado ....................................... 12
 *   `else { if (...) {...} }` anidado .......................... 12
 *   condicion en POSITIVO (0x30/0x31 primero) .................. 41  <- peor, orden invertido
 *   guarda invertida con `return` temprano dentro de la rama .... 12
 *   variable "done" para forzar un punto de union ............... 12
 *
 * No he encontrado forma en C de impedir que mwcc duplique un epilogo de una sola instruccion.
 * Si aparece un crack para eso, esta familia (4 miembros) cae sola.
 *
 * Checklist hecho: arity de los cinco callees verificada contra el arbol; modo ARM. */

extern int func_ov022_02083f0c(void);
extern void func_ov002_0204cdf4(int a, int b, int c);
extern int func_02030788(void);
extern int func_ov022_020ad718(int self);
extern void func_ov022_020ad588(int self);

void func_ov048_020b359c(int self) {
    int st = *(int *)(self + 0x6bc);
    int *blk = (int *)(self + 0x2c + 0x2c00);
    if (st != 0x30 && st != 0x31) {
        if (blk[1] == 1) {
            func_ov002_0204cdf4(func_ov022_02083f0c(), 0, 0);
            blk[1] = 0;
        }
    } else {
        if (*(unsigned char *)(self + 8) == func_02030788()) {
            blk[1] = func_ov022_020ad718(self);
            func_ov022_020ad588(self);
        }
    }
}
