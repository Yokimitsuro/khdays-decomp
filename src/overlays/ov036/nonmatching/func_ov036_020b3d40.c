/* NO INTENTADA -- bloqueada por el residuo r7/sb, 2026-07-19.
 *
 * Esta funcion tiene **DOS** bucles con la forma del residuo descrito en
 * src/overlays/ov047/nonmatching/func_ov047_020b3b40.c (nota canonica): el intercambio r7 <-> sb
 * entre el puntero `p` y el temporal `row + off`. Con dos bucles serian ~14 bytes.
 *
 * No la he escrito: seria la septima familia aparcada por lo mismo y ya hay ~24 funciones
 * bloqueadas con ~70 formas descartadas. Cuando aparezca el crack, esta cae con las demas.
 *
 * Detectada con tools/poolmap.py antes de escribir una linea de C -- el mapa del pool y el
 * `add r7, r2, r8` / `str sb, [r7, #0x130]` la delatan de un vistazo.
 *
 * Familia de 4. Modo ARM. Bucles de 0xc y 2 iteraciones, paso 0x1c8, campos 0x134 y 0x2e4. */
