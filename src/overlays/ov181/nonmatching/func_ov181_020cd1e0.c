/* func_ov181_020cd1e0 -- cabeza de una familia de 10 miembros (ov181..ov183 y compañia).
 *
 * Semantica COMPLETA: pide al gestor el objetivo actual (func_ov107_020cab14, que devuelve el
 * nodo y escribe la distancia al cuadrado en la salida de pila). Si no hay objetivo, marca el
 * modo 2 en el byte 0x1c7 del propietario y termina el estado sin sucesor. Si lo hay: resta a
 * la raiz de la distancia los dos radios (campo 0x80 de objetivo y propietario), fija el
 * temporizador en +0x20 a `campo_0x2c * 30 / 20`, calcula el rumbo hacia el objetivo con
 * VEC_Subtract + func_020050b4, interpola la orientacion (func_0202f384 + func_01ffa724 con
 * peso 0x100) y, si el byte de bloqueo de +0xc esta libre, reafina al propietario (modo 3) y
 * encadena func_ov181_020cd300.
 *
 * EMPATE: DOS BYTES. El ROM usa r7 para `target` y r6 para `owner`; mwcc los reparte al reves.
 * Instruccion por instruccion identico en todo lo demas.
 *
 * Ejes agotados el 2026-07-19:
 *   - 120 permutaciones del orden de declaracion (las 5 locales): TODAS dan lo mismo. Aqui el
 *     crack de "orden de declaracion = orden de registros" NO aplica.
 *   - Formas del guard: probar `target == 0` vs `s[4] == 0`; definir target antes o despues del
 *     guard; el store como `s[4] = (int)(target = ...)`. Esto SI bajo de 5 a 2 bytes -- la forma
 *     buena es `s[4] = (int)func(...); target = (int *)s[4];`.
 *   - Quitar `owner` (mete 14 bytes), quitar `target`, meter los dos en un helper `inline`
 *     (77 bytes: el helper cambia el orden de evaluacion entero).
 *   - Unir `dist` y el Vec3 en una sola struct de pila: 2 bytes igual.
 *   - 12 combinaciones de tipo (int*/char*/void*/unsigned* para cada uno).
 *   - **Los 27 compiladores** (tools/allcc.py): todas las 2.0/3.0 y las dsi hasta 1.3p1 dan
 *     EXACTAMENTE 2; las dsi 1.6 dan 10. Ninguna acierta.
 *
 * Lo que queda por probar, si alguien vuelve: que decide mwcc entre r6 y r7 para dos locales
 * vivas a la vez cuando el orden de definicion no manda. Aqui `owner` tiene 1 uso y `target` 2,
 * y el ROM le da el registro BAJO al de menos usos -- justo al reves que nuestra build. Si eso
 * se confirma en otra funcion, es una regla nueva y desbloquea esta familia entera.
 */
typedef struct { int x, y, z; } Vec3;

extern int *func_ov107_020cab14(int owner, int *distOut);
extern void func_0203c634(int *self, int action, void *cb);
extern int FX_Sqrt(int x);
extern void VEC_Subtract(void *a, void *b, Vec3 *dst);
extern int func_020050b4(int x, int z);
extern void func_0202f384(void *dst, int src, void *tbl);
extern void func_01ffa724(int t, void *a, void *b);
extern void func_ov107_020c9264(int owner, int mode, int arg);
extern void func_ov181_020cd300(void);
extern int data_02042258;

void func_ov181_020cd1e0(int *self) {
    int dist;
    Vec3 v;
    int *s = (int *)self[1];
    int *target;
    int *owner;

    s[4] = (int)func_ov107_020cab14(*s, &dist);
    target = (int *)s[4];
    if (target == 0) {
        *(char *)(*s + 0x1c7) = 2;
        func_0203c634(self, *(signed char *)((char *)self + 0x20), 0);
        return;
    }
    owner = (int *)*s;
    dist = FX_Sqrt(dist) - (owner[0x20] + target[0x20]);
    s[8] = *(int *)(*self + 0x2c) * 0x1e / 20;
    VEC_Subtract((char *)s[4] + 0x190, (void *)s[1], &v);
    s[6] = func_020050b4(v.x, v.z);
    func_0202f384((char *)s + 0x54, *s + 0xa0, &data_02042258);
    func_01ffa724(0x100, (char *)s + 0x54, (char *)s + 0x54);
    if (*(unsigned char *)s[3] != 0) {
        return;
    }
    func_ov107_020c9264(*s, 3, 1);
    func_0203c634(self, *(signed char *)((char *)self + 0x20), (void *)&func_ov181_020cd300);
}
