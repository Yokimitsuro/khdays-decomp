/* Macros de funcion para los .s que genera dsd (sintaxis GNU as).
   Solo fijan el modo de instruccion; el alineado lo emiten los .s con .align. */

.macro arm_func_start name
    .arm
.endm

.macro arm_func_end name
.endm

.macro thumb_func_start name
    .thumb
    .thumb_func
.endm

.macro thumb_func_end name
.endm
