/* EQUIVALENT BUT NOT BYTE-EXACT -- 7 bytes, 2026-07-18.
 *
 * Tamaño y estructura correctos; queda una permutacion entre los dos punteros: el ROM tiene
 * `p` (el fijo, base+0x2c2c) en r1 y el que avanza en r3; mwcc los pone al reves.
 *
 * Camino recorrido, por si sirve de mapa:
 *   indexando `p + i * 0x10c` (sin acumulador) .................. size +8
 *   con acumulador explicito en el `for` ........................ 24
 *   ★ + barrido de las 12 permutaciones de declaracion validas ... 7   <- este fichero
 *   dos punteros separados para los dos bucles (r3 y r8) ......... 7
 *   el que avanza inicializado en su declaracion (`char *q = p;`)  23
 *
 * ⚠ Nota util: aqui el acumulador explicito SI hace falta (+8 sin el). Es lo contrario de
 * func_ov039_020b45c0, donde sobraba. La diferencia esta en el ROM: alli el init del acumulador
 * caia DESPUES del test de salida (señal de que lo invento el compilador) y aqui cae ANTES,
 * junto con las demas inicializaciones. **Mira donde esta el init antes de decidir.**
 *
 * Familia de 4. Modo ARM. */

extern void func_0202a634(int a, void *b, int c, int d);
extern void func_ov042_020b3e20(int base);
extern int data_ov042_020b4800;
extern int data_ov042_020b47b4;

void func_ov042_020b3d34(void) {
    char *q;
    int base = *(int *)&data_ov042_020b4800;
    int i;
    char *p = (char *)(base + 0x2c + 0x2c00);
    *(int *)(base + 0x2000 + 0xc2c) = 0;
    for (i = 0, q = p; i < 7; i++, q += 0x10c) {
        *(int *)(q + 0x14) = 0;
    }
    for (i = 0, q = p + 0x18; i < 7; i++, q += 0x10c) {
        func_0202a634((int)q, &data_ov042_020b47b4, 1, *(unsigned char *)(base + 9) + 7);
    }
    func_ov042_020b3e20(base);
}
