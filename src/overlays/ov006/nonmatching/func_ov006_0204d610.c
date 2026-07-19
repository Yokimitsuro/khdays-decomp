/* func_ov006_0204d610 -- remapea el id de entrada de menu a su hueco de recurso.
 * Cabeza de una pareja (el gemelo es func_ov008_0207928c).
 *
 * Semantica COMPLETA y verificada caso por caso: 0->0xd, 1->2, 2->4, 3->0xc, 4->8, 5->0xf,
 * 6->3, 7->1, 8->6, 9->9, 10->0xa, 11->7, 12->0 (no tiene hueco), 13->0xe, 14->0x10, 15->5,
 * 16->0xb, 17->0x11, 18->0x12; cualquier otro id, 0.
 *
 * EMPATE: UN byte, y esta en la tabla de saltos. La entrada del caso 12 (que esta vacio):
 *     ROM   b 0xb8   -> que a su vez es el `b 0xe8` del caso 11
 *     mwcc  b 0xe8   -> directo al final
 * Los dos son correctos; mwcc simplifica el salto doble y el ROM no. Las 232 instrucciones
 * restantes casan exactamente.
 *
 * Probado el 2026-07-19: el caso vacio escrito al principio, en medio y al final del switch;
 * con `goto` a una etiqueta al final; y haciendo que el caso 11 caiga por dentro del 12 (sin
 * `break`) -- que era la hipotesis buena, porque el destino del ROM es justo el `b` del caso 11.
 * Ninguna cambia la entrada de la tabla: no hay palanca en el fuente para un salto doble.
 */
/* Remaps a menu entry id onto its resource slot. Entry 12 has no slot and falls back to 0, the
 * same as anything out of range. */
int func_ov006_0204d610(int id) {
    int slot = 0;
    switch (id) {
    case 0:  slot = 0xd;  break;
    case 1:  slot = 2;    break;
    case 2:  slot = 4;    break;
    case 3:  slot = 0xc;  break;
    case 4:  slot = 8;    break;
    case 5:  slot = 0xf;  break;
    case 6:  slot = 3;    break;
    case 7:  slot = 1;    break;
    case 8:  slot = 6;    break;
    case 9:  slot = 9;    break;
    case 10: slot = 0xa;  break;
    case 11: slot = 7;    break;
    case 12: break;
    case 13: slot = 0xe;  break;
    case 14: slot = 0x10; break;
    case 15: slot = 5;    break;
    case 16: slot = 0xb;  break;
    case 17: slot = 0x11; break;
    case 18: slot = 0x12; break;
    }
    return slot;
}
