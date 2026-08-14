"""Semantic receipt for func_ov002_0205aa3c."""
import subprocess
import sys

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_PanelDrawCounter"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Antes FUN_arm9_ov002__0205aa3c. Dibuja un contador de dos digitos en el "
     "tile map del recurso de item 0x0b: parte el valor en decenas y unidades "
     "con la multiplicacion magica 0x66666667 leida del pool en 0x0205ab84, y "
     "escribe cada digito como un par de tiles de 1x2 mediante "
     "WriteTileQuad9000. Termina marcando la entrada 0x0b con Ov002_SelectEntry. "
     "La llama el repaint ya casado func_ov002_0205b7dc en el camino de clase 0 "
     "con kind 0."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Aridad CINCO, confirmada en el desensamblado: r0, r1, r2 y r3 se leen "
     "antes de escribirse y el quinto se lee con ldr r0,[sp,#0x20], es decir "
     "por encima de los 32 bytes que empuja el prologo. Renombrados a nSlot, "
     "nValue, nColumn, bRightAlign y bShowZero. Read-back PARAMS 5 con "
     "almacenamiento r0, r1, r2, r3 y Stack[0x0]."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "Solo hay un hueco de pila y NO es una variable del programa: el prologo "
     "no tiene sub sp, empuja r3 exclusivamente para crear el area del quinto "
     "argumento saliente de las cuatro llamadas de cinco argumentos a "
     "WriteTileQuad9000 (str rX,[sp,#0]). Renombrado a aOutArgSlot y tipado "
     "int para que no se confunda con un local real. Read-back LOCALS 1. El "
     "resto de valores vive en registros."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "void Ov002_PanelDrawCounter(int nSlot, int nValue, int nColumn, "
     "int bRightAlign, int bShowZero). Retorno void: r0 no se define en la "
     "salida, el epilogo restaura pc directamente y el unico caller ignora el "
     "resultado."),
    ("layout_decision", "no_new_layout"),
    ("layout_evidence",
     "No descubre layout nuevo y no existe objeto tipable propio: la funcion no "
     "toca ningun campo de Ov002PanelSession ni de ninguna otra estructura. "
     "Trabaja sobre el tile map crudo que devuelve Ov002_GetItemResource(0x0b), "
     "cuyo tipo ya vive en el prototipo del escritor: read-back de "
     "WriteTileQuad9000 da ushort *param_1 con cuatro ushort, que es "
     "exactamente el tipado que exigen las conversiones lsl #16 / lsr #16 del "
     "ROM en los cuatro argumentos de tile. Se reviso ese tipo existente y se "
     "reutiliza sin cambios. La geometria descubierta (fila = nSlot*2+12, "
     "32 entradas u16 por fila, bases de glifo 0x201 izquierda y 0x20b derecha, "
     "+0x20 la mitad inferior, 0x11f el tile en blanco) queda registrada en el "
     "comentario de funcion de Ghidra porque son constantes de un mapa de "
     "tiles, no campos de un registro."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "Read-back por direccion en el address space arm9_ov002 de los cinco "
     "parametros int con su almacenamiento, del local aOutArgSlot como int en "
     "Stack[-0x20], y de los prototipos de los tres callees: "
     "int Ov002_GetItemResource(int nItemId), Ov002_SelectEntry(int) y "
     "WriteTileQuad9000(ushort *, ushort, ushort, ushort, ushort). No se creo "
     "ni extendio ningun tipo porque no hacia falta."),
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
     "tools/audit_unnamed.py deja ov002 en 244 sin nombre: la funcion sale de "
     "la cuenta al recibir nombre semantico, asi que la deuda baja y no se "
     "introduce ninguna nueva."),
    ("audit_struct_sync_no_new_debt", "true"),
    ("audit_struct_sync_evidence",
     "tools/audit_struct_sync.py sale con codigo 0 y no lista ningun conflicto. "
     "Esta tanda no creo ni modifico ningun tipo, asi que no puede introducir "
     "variantes rivales."),
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
