/* EQUIVALENT BUT NOT BYTE-EXACT -- 15 bytes, 2026-07-18.
 *
 * Queda una PERMUTACION DE REGISTROS: el ROM usa self=r6, idx-extendido=r8, cero=r7; mwcc usa
 * self=r7, idx=r6, cero=r8. Todo lo demas (tamaño, bloques, la extension unica, las direcciones
 * recalculadas dentro del bucle) ya casa.
 *
 * El camino hasta aqui vale mas que el resultado, porque acota tres cosas por separado:
 *   forma plana, `short idx`, callee con `short` ............... size +4 (hoistea 3 invariantes)
 *   forma plana, `int idx` + `(short)idx` en la llamada ........ size +8
 *   forma plana, `short idx`, callee con `int` ................. size +4
 *   ★ struct-typed (campos en vez de `self + 0xNNN`) ........... size -4  <- quita el hoisting
 *   struct-typed + `short idx` ................................ size -4  (falta la extension)
 *   ★ struct-typed + `int idx` + `(short)idx` ................. 15      <- forma correcta
 *   ...y ademas un local `short si = idx;` (antes o despues de `i`) ... 15
 *
 * Dos lecciones ya escritas en codegen-cracks.md y confirmadas aqui:
 * 1. **El struct-typed impide que mwcc hoistee las direcciones invariantes del bucle.** Con
 *    `self + 0x24c` mwcc las sube a callee-saved y la lista del `push` crece de 6 a 10 registros;
 *    con `self->anim` las recalcula dentro, como el ROM.
 * 2. **`short` en el PARAMETRO no genera extension**: el ABI de ARM asume que el llamador ya
 *    extendio. La extension unica al principio (`lsl #0x10 / asr #0x10` guardada en un
 *    callee-saved) sale de un parametro `int` con `(short)` en el uso, que mwcc CSEa.
 *    Es la forma OPUESTA a func_ov038_020b3fe8, donde el ROM re-extendia en cada llamada y habia
 *    que poner el `short` en el prototipo del callee. **Las dos formas existen; mira si el ROM
 *    extiende una vez o N veces antes de elegir.**
 *
 * Familia de 4. Modo ARM. Arity de los tres callees verificada. */

extern void func_02014dc4(void *a, int b);
extern void func_0202accc(void *a, unsigned short b, int c, int d);
extern void func_01fff774(void *a, unsigned short b, int c);

typedef struct {
    char pad0[0x24c];
    char anim[0x258 - 0x24c];
    int slots[5];
    char pad26c[0x26c - 0x26c];
    char tracks[0x354 - 0x26c];
    int table;
} Self;

void func_ov048_020b4050(Self *self, int idx) {
    int i;
    for (i = 0; i < 5; i++) {
        if (self->slots[i] != 0) {
            func_02014dc4(self->tracks, self->slots[i]);
            self->slots[i] = 0;
        }
        func_0202accc(self->anim, i, self->table, (short)idx);
        func_01fff774(self->anim, i, 0);
    }
}
