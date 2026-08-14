"""Semantic receipt for func_ov002_0205ae08."""
import subprocess
import sys

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_PanelRefreshRowHeader"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Antes FUN_arm9_ov002__0205ae08. Refresca la cabecera de una fila del "
     "panel: elige el tile de glifo nRow*16+0xd0 y el atributo 0xf o 0xe segun "
     "bEnabled, los empuja al widget del slot nRow+1 con suelo en 3, fija el "
     "estado de la fila y despues dibuja el contador de dos digitos o limpia "
     "sus dos celdas. La llama el rebuild ya casado func_ov002_0205bff4 desde "
     "SIETE sitios de su dispatch de modo, mas que ninguna otra callee suya."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Aridad TRES, confirmada en el desensamblado: solo r0, r1 y r2 se leen "
     "antes de escribirse, y no hay ninguna lectura por encima del marco. "
     "Renombrados a nRow, bEnabled y bRightAlign. El tercero se llama asi "
     "porque es exactamente el mismo eje que dentro de "
     "Ov002_PanelDrawCounter: aqui elige la columna 11 o la 10 para el "
     "borrado, y se le pasa tal cual a esa funcion como su bRightAlign."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "Un unico hueco de pila y NO es una variable del programa: el prologo no "
     "tiene sub sp y empuja r3 solo para crear el area del quinto argumento "
     "saliente de las dos llamadas de cinco argumentos (str rX,[sp,#0] en "
     "0x0205ae94 y 0x0205aec0). Renombrado a aOutArgSlot y tipado int. "
     "Read-back LOCALS 1. El resto vive en registros: r5 el puntero de sesion, "
     "r6 bRightAlign, r7 el slot y r4 el indicador de modo especial."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "void Ov002_PanelRefreshRowHeader(int nRow, int bEnabled, "
     "int bRightAlign). Retorno void: el epilogo restaura pc tras la ultima "
     "llamada sin definir r0, y ningun caller usa el resultado."),
    ("layout_decision", "reused"),
    ("layout_evidence",
     "Reutiliza el layout existente sin cambiarlo. Lee exactamente dos campos "
     "del objeto de sesion y los dos ya estaban tipados y verificados por "
     "read-back: nField0008 int en +0x08, que establecio la tanda de "
     "func_ov002_0205b7dc, y wField0016 ushort en +0x16, que ya usaba el mismo "
     "repaint. El ancho de 16 bits de wField0016 lo confirma el ROM de forma "
     "independiente: lo carga con ldrh en 0x0205ae30 y 0x0205aec4. El pool slot "
     "arm9_ov002.bss::0207f620 sigue tipado Ov002PanelSession *. No aparece "
     "ningun offset nuevo."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "Read-back por direccion en arm9_ov002: los tres parametros int con su "
     "almacenamiento, aOutArgSlot int en Stack[-0x18], los campos nField0008 y "
     "wField0016, el pool slot como Ov002PanelSession *, y los prototipos de "
     "los callees, incluido func_ov002_0205ad5c con su tercer parametro ushort, "
     "que es lo que explica las conversiones lsl #16 / lsr #16 del ROM. No se "
     "creo ni extendio ningun tipo."),
    ("transactions_closed", "true"),
    ("transactions_evidence",
     "Los tres scripts terminaron con SCRIPT COMPLETED SUCCESSFULLY sin dejar "
     "transaccion propia abierta ni errores de endTransaction."),
    ("program_saved_readback", "true"),
    ("save_evidence",
     "save_program en llamada separada devolvio Program saved successfully y el "
     "read-back posterior informa CHANGED False."),
    ("audit_unnamed_no_new_debt", "true"),
    ("audit_unnamed_evidence",
     "tools/audit_unnamed.py: la funcion sale de la cuenta de ov002 al recibir "
     "nombre semantico, asi que la deuda baja y no se introduce ninguna nueva."),
    ("audit_struct_sync_no_new_debt", "true"),
    ("audit_struct_sync_evidence",
     "tools/audit_struct_sync.py sale con codigo 0 y no lista "
     "Ov002PanelSession con variantes en conflicto. Esta tanda no toco ningun "
     "tipo."),
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
