"""Semantic receipt for func_ov002_0205afb4."""
import subprocess
import sys

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_PanelRepaintRow"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Antes FUN_arm9_ov002__0205afb4. Repinta una fila del panel. La celda "
     "aCells[nIndex] gobierna todo: si su primer byte es 0xff, o nIndex es 0x0f "
     "o mayor, la fila cae al bloque de glifos en blanco 0x3d0 sin estilo; si "
     "no, el bloque es nIndex*16 + 0x130 y el estilo sale de la busqueda de "
     "grupo en 0x0205af40 sobre ese mismo byte, salvo que nState sea cero. La "
     "llama el rebuild func_ov002_0205bff4 DOS veces seguidas, para la fila que "
     "sale y la que entra."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Aridad CINCO, confirmada en el desensamblado: r0, r1, r2 y r3 se copian a "
     "callee-saved en el prologo y el quinto se lee tres veces con "
     "ldr rX,[sp,#0x28], por encima de los 36 bytes del push mas los 4 del "
     "sub sp. Renombrados a nIndex, nSlot, nColumn, bEnabled y bRightAlign. "
     "bEnabled solo elige la paleta 0xf o 0xe; bRightAlign se reenvia a las dos "
     "callees y ademas elige cual de las dos tablas de traduccion se usa."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "Un unico hueco de pila y NO es una variable del programa: es el area del "
     "quinto argumento saliente de la escritura de etiqueta (str r7,[sp,#0] en "
     "0x0205b048). Renombrado a aOutArgSlot y tipado int; read-back LOCALS 1. "
     "Aqui el marco SI lleva sub sp #4, a diferencia de las funciones hermanas, "
     "porque los nueve registros empujados ya dejan la pila alineada. El resto "
     "vive en registros: r5 el puntero de sesion, r6 el estilo, r4 el bloque de "
     "glifos, r10 nIndex, r9 nSlot, r8 nColumn y r7 primero bEnabled y luego "
     "bRightAlign."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "void Ov002_PanelRepaintRow(int nIndex, int nSlot, int nColumn, "
     "int bEnabled, int bRightAlign). Retorno void: el epilogo restaura pc tras "
     "las dos marcas de entrada sin definir r0, y el rebuild ignora el "
     "resultado."),
    ("layout_decision", "created"),
    ("layout_evidence",
     "Layout nuevo en los datos, ademas de reutilizar los del struct. Las dos "
     "tablas de traduccion de estilo en 0x0207de70 y 0x0207de80 no tenian tipo "
     "(read-back previo: type=None). El ROM las indexa con "
     "ldr rX,[base, estilo lsl #2], asi que son arrays de palabras, y "
     "symbols.txt las acota exactamente: el siguiente simbolo esta en "
     "0x0207de80 y en 0x0207de90 respectivamente, es decir DIECISEIS bytes cada "
     "una. Tipadas int[4], leidas de vuelta con len=16. Del struct se reutilizan "
     "sin cambios nState int en +0x10 y aCells Ov002PanelCell[551] en +0x32, "
     "y esta funcion vuelve a confirmar la interpretacion de celda de dos "
     "bytes: lee el primer byte en +0x32 y el segundo en +0x33 con el mismo "
     "indice desplazado a la izquierda uno."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "Read-back por direccion: los cinco parametros int con su almacenamiento, "
     "aOutArgSlot int en Stack[-0x28], nState int en +0x10 y aCells "
     "Ov002PanelCell[551] de 1102 bytes en +0x32 con Ov002PanelCell len=2, las "
     "dos tablas como int[4] de 16 bytes en el address space arm9_ov002, y el "
     "pool slot arm9_ov002.bss::0207f620 como Ov002PanelSession *."),
    ("transactions_closed", "true"),
    ("transactions_evidence",
     "Los cuatro scripts terminaron con SCRIPT COMPLETED SUCCESSFULLY sin dejar "
     "transaccion propia abierta ni errores de endTransaction, incluido el que "
     "borra y recrea el dato de las dos tablas."),
    ("program_saved_readback", "true"),
    ("save_evidence",
     "save_program en llamada separada tras la tanda de tipos devolvio Program "
     "saved successfully y el read-back posterior informa CHANGED False."),
    ("audit_unnamed_no_new_debt", "true"),
    ("audit_unnamed_evidence",
     "tools/audit_unnamed.py: la funcion sale de la cuenta de ov002 al recibir "
     "nombre semantico, asi que la deuda baja y no se introduce ninguna nueva."),
    ("audit_struct_sync_no_new_debt", "true"),
    ("audit_struct_sync_evidence",
     "tools/audit_struct_sync.py sale con codigo 0 y no lista Ov002PanelSession "
     "ni Ov002PanelCell con variantes en conflicto. No se creo ningun struct "
     "nuevo: los tipos anadidos son arrays de int sobre datos que estaban sin "
     "tipar."),
]

fail = 0
for field, value in MARKS:
    r = subprocess.run([sys.executable, ".claude/hooks/khdays_control.py",
                        "semantic-mark", field, value],
                       capture_output=True, text=True)
    if r.returncode != 0:
        fail += 1
        print("%-30s FAIL %s" % (field, (r.stdout + r.stderr).strip()[:120]))
print("failures:", fail)
