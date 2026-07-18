/* EQUIVALENT BUT NOT BYTE-EXACT -- 33 bytes, 2026-07-19.
 *
 * TERCERA aparicion del residuo de **SALIDA UNICA**: el ROM salta con `bne <fin>` a un `pop`
 * compartido (tres veces aqui) y mwcc emite `popne` en cada guarda. Las otras dos:
 *   src/overlays/ov048/nonmatching/func_ov048_020b359c.c
 *   src/overlays/ov036/nonmatching/func_ov036_020b35f8.c
 *
 * ★ NEGATIVO UTIL (2026-07-19): reescribirla en forma **anidada con salida unica real** --
 *   `if (a() == 0 && b() == 0) { ...; if (c() == 0) { ...; } }` -- deja los `popne` EXACTAMENTE
 *   igual (33 bytes, mismos tres). O sea que no es la forma del control de flujo en C: mwcc
 *   convierte cualquier salida en un epilogo predicado cuando el epilogo es una sola instruccion.
 *   Con esto la clase queda acotada: **no se ataca desde la estructura del fuente.**
 *
 * Residuo secundario (mismo que en el park de ov036_020b35f8): en el bloque final el ROM carga
 * `self` en r0 al FINAL, justo antes de la llamada, y usa r0/r1/r2 en otro orden; mwcc precarga
 * `mov r0, r4` y desplaza los tres registros.
 *
 * Familia de 4. Modo ARM. Arity de los seis callees verificada. */

extern int func_ov022_02083f90(void);
extern void func_ov022_0209145c(int a, int b);
extern void func_ov022_02091474(int a);
extern int func_ov022_020912d8(int a);
extern int func_02030788(void);
extern void func_ov022_020ad588(int self);

void func_ov047_020b3630(int self) {
    func_ov022_0209145c(*(int *)(self + 0x2000 + 0x644), func_ov022_02083f90());
    func_ov022_02091474(*(int *)(self + 0x2000 + 0x644));
    if (func_ov022_020912d8(*(int *)(self + 0x2000 + 0x644)) != 0) return;
    if (func_02030788() != 0) return;
    *(long long *)((char *)self + 0x464) |= 0x10000;
    if (func_02030788() != 0) return;
    *(long long *)((char *)self + 0x46c) |= 0x10000;
    func_ov022_020ad588(self);
}
