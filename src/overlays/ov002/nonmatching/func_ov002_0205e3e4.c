extern char *data_ov002_0207f620;
extern void func_ov002_0205cebc(void);
extern void func_ov002_0205cc44(void);
extern int func_ov002_0205a4ec(void);
extern int func_ov002_0205a3f0(int *out, int slot);
extern long long func_02020400(int a, int b);
extern void func_ov002_0205bff4(int a);
extern void func_ov002_0205c87c(int a);

/* Steps the cursor back one entry and, if the entry resolves to kind 3, plays the
 * move sound and opens it. */
void func_ov002_0205e3e4(void) {
    char *self = *(char **)&data_ov002_0207f620;
    int out;
    int n;
    func_ov002_0205cebc();
    func_ov002_0205cc44();
    n = func_ov002_0205a4ec();
    if (n >= 1 && (unsigned char)self[4] >= n) {
        self[4] = (char)(n - 1);
    }
    if (func_ov002_0205a3f0(&out, (unsigned char)self[1]) == 3) {
        func_02020400((unsigned char)self[4], 6);
        func_ov002_0205bff4((unsigned char)self[0]);
        func_ov002_0205c87c(out);
    }
}

/* PARK 2026-07-19: 2 bytes. Instruccion por instruccion identico; el ROM carga la palabra del
 * pool en r2 y mwcc en r0. Clase "el ROM se salta el registro libre mas bajo" (deferred-ties).
 * Probado: declaracion como inicializador / como sentencia, orden de declaraciones (3 permutaciones),
 * y el global declarado como char** con indice. Todo da r0. No re-triturar. */
