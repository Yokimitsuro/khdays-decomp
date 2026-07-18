/* EQUIVALENT BUT NOT BYTE-EXACT -- size +8 (dos instrucciones de mas), 2026-07-19.
 *
 * La funcion hace tres operaciones de bitfield y **las tres formas casan salvo una truncacion**:
 *   `hi &= ~1`   -> el ROM SI trunca (`lsl #0x10 / lsr #0x10`) antes de mezclar. Casa.
 *   `hi |= 0x82` -> el ROM **NO** trunca; mwcc emite el par lsl/lsr igualmente. +8 bytes.
 *   `f &= ~1` (campo de 8 bits en contenedor `unsigned int`) ... casa.
 *
 * La logica del ROM es coherente: `~1` es 0xFFFFFFFE y puede ensuciar los bits altos, asi que
 * hay que truncar; `| 0x82` no puede salirse de 8 bits, asi que no hace falta. mwcc no hace esa
 * deduccion con la forma que escribo.
 *
 * Probado y descartado:
 *   `hi = hi | 0x82` en vez de `|=` ......................... +8
 *   temporal `unsigned char t = hi; hi = t | 0x82;` ......... +12
 *   campo como `unsigned char hi;` en un struct plano ....... -20 (rompe la extraccion entera)
 *
 * Queda por probar: alguna forma que le diga a mwcc que el valor cabe en 8 bits sin cambiar la
 * extraccion (¿un bitfield de 8 en contenedor `unsigned int` para ESTA operacion, como el tercer
 * caso, que si casa?). Es la pista mas concreta: el tercer bitfield de la funcion usa contenedor
 * de 32 bits y no sufre el problema.
 *
 * Familia de 4. Modo ARM. */

extern void func_0203c634(int *self, int idx, void *cb);
extern void func_ov123_020cdae4(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct b8 { unsigned int f : 8; };

void func_ov123_020cda50(int *self) {
    int *s = (int *)self[1];
    ((struct hw60 *)(*s + 0x60))->hi &= ~1;
    ((struct hw60 *)(*s + 0x60))->hi |= 0x82;
    ((struct b8 *)(*(int *)(*s + 0x388) + 8))->f &= ~1;
    func_0203c634(self, *(signed char *)((char *)self + 0x20), (void *)&func_ov123_020cdae4);
}
