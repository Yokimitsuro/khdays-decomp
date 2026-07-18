/* EQUIVALENT BUT NOT BYTE-EXACT -- 33 bytes, 2026-07-19.
 *
 * Dos residuos, y el primero ya tiene precedente:
 *
 * 1. **SALIDA UNICA vs epilogo duplicado** (misma clase que
 *    src/overlays/ov048/nonmatching/func_ov048_020b359c.c): el ROM hace `bne <fin>` hacia un
 *    `pop` compartido en las dos guardas; mwcc emite `popne` en cada una. Es la SEGUNDA funcion
 *    donde aparece, asi que es una clase recurrente y no una casualidad. Sigo sin encontrar forma
 *    en C de impedir que mwcc duplique un epilogo de una sola instruccion.
 *
 * 2. El bloque final: el ROM usa **r0 como scratch** para las dos constantes (`mov r0,#3 / strb /
 *    mov r0,#1 / strb`) y carga `self` en r0 al final, justo antes de la llamada. mwcc precarga
 *    `mov r0, r4` y se ve obligado a usar r1 para las constantes. Probado con un puntero local
 *    (`signed char *f = self + 0x47a; f[0]=3; f[1]=1;`): size +4, peor.
 *
 * Tambien probado: partir la primera guarda en un `return` temprano propio -> 33, igual.
 *
 * Lo demas casa: la cadena predicada de tres condiciones (`tst` + `ldreq`/`cmpeq`), los offsets
 * partidos (0x1a8+0xc00, 0x2c+0x2c00, 0x2a00+0xba) y el orden de las cuatro llamadas.
 *
 * Familia de 4. Modo ARM. */

extern int func_0202aee0(int a, int b);
extern void func_ov002_020521e4(int a, int b, int c, int d);
extern int func_ov022_02083f90(void);
extern void func_ov036_020b4c50(int a, int b);
extern int func_02030788(void);
extern void func_ov022_020ad588(int self);

void func_ov036_020b35f8(int self) {
    int t = func_0202aee0(*(int *)(self + 0x20) + 4, 0);
    func_ov002_020521e4(self + 0x1a8 + 0xc00, self + 0x2c + 0x2c00,
                        *(short *)(self + 0x2a00 + 0xba), t);
    func_ov036_020b4c50(self, func_ov022_02083f90());
    if (func_02030788() == 0 &&
        (*(int *)self & 0x10000) == 0 &&
        *(int *)(self + 0x6bc) == 0x30 &&
        *(int *)(self + 0x7b0) == 0xf000) {
        *(signed char *)(self + 0x47a) = 3;
        *(signed char *)(self + 0x47b) = 1;
        func_ov022_020ad588(self);
    }
}
