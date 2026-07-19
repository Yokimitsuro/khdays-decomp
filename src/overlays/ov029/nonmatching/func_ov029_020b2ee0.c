/*
 * func_ov029_020b2ee0 -- Ov029_AcquireOverlaySlot. UNFINISHED (96/96 bytes, no match).
 * Es la ULTIMA funcion de ov029 (1/2 -> 2/2), asi que casarla cierra el modulo.
 *
 * * ESTA FUNCION ES **THUMB**. Verifica con `--thumb` o todos los numeros que saques
 * son ruido.
 *
 * QUE HACE (resuelto 2026-07-19; antes la nota lo describia como "slots" genericos):
 *   func_0201e470 es un envoltorio de **FS_LoadOverlay** y func_0201e4a8, la que usa la
 *   otra funcion del overlay, lo es de **FS_UnloadOverlay**. Las dos funciones de ov029
 *   son por tanto un par cargar/descargar sobre una tabla de 4 huecos:
 *
 *     data_ov029_020b3200[4]   los 4 huecos; cada uno guarda el ID del overlay que tiene
 *                              cargado, o -1 si esta libre.
 *     data_ov029_020b30b0[]    filas de 4 ints: por cada "grupo", que ID de overlay le
 *                              corresponde en cada hueco (-1 = ese grupo no puede usarlo).
 *     data_ov029_020b2f70[]    filas de 4 punteros a funcion: el hook de init de cada
 *                              pareja (grupo, hueco).
 *
 *   Recorre los huecos de 3 hacia 0 y se queda con el primero que este libre Y para el que
 *   el grupo tenga un overlay. Lo publica en el hueco, llama a FS_LoadOverlay y ejecuta el
 *   hook. Devuelve el ID cargado, o -1 si no habia sitio.
 *   func_ov029_020b2f40 hace lo contrario: busca el hueco que contiene ese ID y lo pone a -1.
 *
 * ⚠ PARA EL PORT: si NO hay hueco libre, k se queda en -1 y el codigo sigue igualmente.
 *   Llama a FS_LoadOverlay(0, -1) y luego indexa la tabla de hooks con k = -1, o sea que
 *   lee la palabra ANTERIOR a la fila. Es lectura fuera de rango, y esta reproducida tal
 *   cual porque es lo que hace el ROM. No lo "arregles" al portarlo sin decidirlo aparte.
 *
 * ⚠ data_ov029_020b3200 y data_ov029_020b320c SON EL MISMO ARRAY: delinks.txt pone .data en
 *   0x020b3200..0x020b3220 y 0x320c cae dentro, es &array[3]. El fuente original escribio un
 *   solo array y tomo su ultimo elemento; los dos simbolos son un artefacto del delinker.
 *   Aqui hay que dejar los dos porque verify_idx compara NOMBRES de reloc y el indice espera
 *   data_ov029_020b320c en el offset 84. (Probada la version de un solo array: mismo residuo
 *   y encima cambia los relocs, asi que no aporta nada.)
 *
 * ---------------------------------------------------------------------------------
 * EL DIFF
 *
 * El bucle necesita los 8 registros bajos de THUMB, y hay DOS candidatos para el unico
 * callee-saved libre (r7):
 *   - el offset en bytes `group<<4`, vivo a traves del bl del final
 *   - el puntero al grupo, muerto antes de ese bl
 * ROM:  guarda el offset en el hueco de r3 del push (`str r1,[sp]` ... `ldr r0,[sp]`) y
 *       mantiene el puntero al grupo en un registro bajo (r7).
 * mwcc: le da r7 al offset y destierra el puntero a `ip`, pagando `mov r0, ip` antes de la
 *       carga indexada (el `ldr rd,[rn,rm]` de THUMB exige registros bajos).
 *
 * El rango de vida del offset EMPIEZA ANTES -- tiene que empezar antes, porque el puntero se
 * calcula A PARTIR de el -- asi que el asignador llega primero al offset y le da r7.
 *
 * ⚠ CORREGIDO 2026-07-19: la nota decia "47/47 instructions" y ninguna de las dos mitades
 * era cierta. Medido con capstone sobre los dos objetos: el ROM tiene **39** instrucciones y
 * el nuestro **38 reales + un `mov r8,r8` de relleno** para alinear el pool. No es
 * instruccion-por-instruccion identico: es UNA MAS CORTO, y los 96 bytes cuadran por el nop.
 * Eso tumba la conclusion que traia la nota ("las dos formas cuestan lo mismo, por eso mwcc
 * no prefiere la del ROM"): mwcc SI tiene motivo, le sale mas corto. Cuenta real:
 *      cabecera: ROM 13 / nuestra 12     bucle: ROM 16 / nuestra 17 (el `mov r0, ip`)
 *      cola:     ROM  6 / nuestra  5     (no hace falta recargar el offset desde [sp])
 *
 * ---------------------------------------------------------------------------------
 * EJES CERRADOS (no los repitas)
 *
 * COMPILADOR: build_sweep completo. Las 12 builds de la linea 2.0/3.0 dan residuo
 *   byte-identico (54 bytes); las lineas 1.2 y dsi ni aciertan el tamano.
 *
 * FLAGS: sacados los flags de los 9 presets de NDS de decomp.me
 *   (/api/preset?platform=nds_arm9) y probados los 10 que nosotros no usamos: -ipa file,
 *   -ipa function, -fp soft, -str reuse, -str noreuse, -sym on, -RTTI off, -msgstyle gcc,
 *   -nosyspath. Los diez dan el MISMO residuo de 54 bytes. Los -ipa (analisis
 *   interprocedural) eran los unicos con posibilidades reales y tampoco tocan nada.
 *
 * TIPADO CON STRUCTS (2026-07-19, sugerido en el Discord de decomp.me): probadas 5 formas
 *   (offset compartido, indice normal `tabla[grupo]`, fila tipada, grupo indexado por k,
 *   hueco indexado por k). Ninguna casa. La de indice normal iguala el numero de
 *   instrucciones del ROM (39, sin nop) pero sigue usando `ip` y cambia los relocs. Se ha
 *   quedado la version tipada de todos modos porque se lee mucho mejor, que era el motivo
 *   de la sugerencia.
 *
 * FORMA DEL FUENTE: ~19 grafias descartadas antes de esto -- local `off` separado frente a
 *   reusar el parametro, el puntero declarado primero, base `char *`, punteros que avanzan,
 *   `for` en vez de `do/while` (100 B, 4 de mas), calcular `e` primero (100 B), decl-init de
 *   una sola expresion, comparar contra `loaded` en vez del literal -1, `unsigned int` en el
 *   offset, `&x[3]` frente a `x + 3`.
 *
 * SIGUIENTE PASO: no queda ninguno a nivel de funcion. Haria falta un idioma que obligue a
 * mwcc a volcar un valor al hueco de argumento del push en vez de darle el ultimo
 * callee-saved, o que acorte el rango de vida del puntero al grupo para que gane el r7.
 * Preguntado en el Discord de decomp.me. Ver la clase de eleccion-de-registro en
 * deferred-ties.md.
 */
typedef void (*OverlayInitFn)(void);

/* Una fila por grupo: que overlay le toca en cada hueco (-1 = no puede usar ese hueco). */
typedef struct {
    int overlayId[4];
} OverlayGroup;

extern OverlayGroup data_ov029_020b30b0[];   /* tabla de grupos */
extern char data_ov029_020b2f70[];           /* filas de 4 OverlayInitFn, 0x10 por grupo */
extern int data_ov029_020b3200[4];           /* huecos: ID cargado, o -1 si libre */
extern int data_ov029_020b320c[];            /* == &data_ov029_020b3200[3]; ver nota arriba */
extern void func_0201e470(int proc, int overlayId);   /* -> FS_LoadOverlay */

int func_ov029_020b2ee0(int proc, int group)
{
    int loaded = -1;
    OverlayGroup *g;
    int *slot = data_ov029_020b320c;   /* recorre los huecos de 3 hacia 0 */
    int *cand;                         /* ...y en paralelo, el ID del grupo para ese hueco */
    int k = 3;

    /* group pasa a ser el offset en bytes y se reusa para las dos tablas; es lo que hace
       el ROM y lo que fuerza el orden de emision (ver la nota del diff). */
    group = group << 4;
    g = (OverlayGroup *)((char *)data_ov029_020b30b0 + group);
    cand = &g->overlayId[3];
    do {
        if (*slot == -1 && *cand != -1) {
            loaded = g->overlayId[k];
            data_ov029_020b3200[k] = loaded;
            break;
        }
        slot--; cand--; k--;
    } while (k >= 0);

    func_0201e470(0, loaded);
    (*(OverlayInitFn *)(data_ov029_020b2f70 + group + k * 4))();
    return loaded;
}
