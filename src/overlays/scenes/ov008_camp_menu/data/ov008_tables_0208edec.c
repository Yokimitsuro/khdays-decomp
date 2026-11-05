/* ov008 .rodata tables, 0x0208edec-0x0208ee84.
 *
 * 5 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_0208edec: Ov008_WorldMap_SetupToolbar
 *   data_ov008_0208edfc: Ov008_WorldMap_SetupToolbar
 *   data_ov008_0208ee0c: Ov008_WorldMap_SetupTextSurfaces
 *   data_ov008_0208ee34: Ov008_WorldMap_SetupTextSurfaces
 *   data_ov008_0208ee5c: Ov008_WorldMap_SetupTextSurfaces
 */

#include "nitro/types.h"

const int data_ov008_0208edec[4] = {
    0, 2, 0, 0,
};

const int data_ov008_0208edfc[4] = {
    0, 1, 0, 0,
};

const int data_ov008_0208ee0c[10] = {
    22, 5, 15, 2, 178, 15, 0, 5,
    0, 32,
};

const int data_ov008_0208ee34[10] = {
    22, 24, 8, 2, 208, 15, 0, 5,
    0, 32,
};

const int data_ov008_0208ee5c[10] = {
    0, 14, 18, 2, 142, 15, 0, 5,
    0, 32,
};
