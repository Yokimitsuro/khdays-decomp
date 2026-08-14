"""Semantic receipt for func_ov002_0205b640."""
import subprocess
import sys

MARKS = [
    ("ghidra_inspected", "true"),
    ("semantic_name", "Ov002_PanelShowValueRow"),
    ("function_rename_readback", "true"),
    ("function_rename_evidence",
     "Antes FUN_arm9_ov002__0205b640. Muestra u oculta una fila de valor del "
     "panel como un par de nodos de seguimiento de tag: mientras "
     "Ov002PanelSession.nState en +0x10 no sea cero desarma los dos y no hace "
     "nada mas; si es cero arma el nodo de etiqueta, rellena el nodo de valor "
     "con nValue bajo el kind 0x11 y lo arma solo si la fila esta visible. Es "
     "el punto de convergencia de las TRES clases de lista del repaint ya "
     "casado func_ov002_0205b7dc."),
    ("parameters_reviewed", "true"),
    ("parameters_evidence",
     "Aridad CINCO, confirmada en el desensamblado: r0, r1, r2 y r3 se leen "
     "antes de escribirse y el quinto se lee dos veces con ldr r0,[sp,#0x18] y "
     "ldr r1,[sp,#0x18], justo por encima de los 24 bytes que empuja el "
     "prologo. Renombrados a nTop, nMain, nValue, bRefresh y bVisible. El "
     "quinto no es solo una condicion: ademas se pasa TAL CUAL como segundo "
     "argumento de la ultima llamada, asi que es el estado armado del nodo de "
     "valor. Read-back PARAMS 5 en r0, r1, r2, r3 y Stack[0x0]."),
    ("locals_reviewed", "true"),
    ("locals_evidence",
     "No hay locales en pila: el marco es push {r3,r4,r5,r6,r7,lr} sin sub sp y "
     "ninguna llamada pasa de tres argumentos, asi que el r3 empujado es solo "
     "relleno de alineacion. Los cuatro parametros de registro se copian a r7, "
     "r6, r5 y r4 para sobrevivir a las llamadas. Read-back LOCALS 0, asi que "
     "no hay nada que renombrar."),
    ("prototype_readback", "true"),
    ("prototype_evidence",
     "void Ov002_PanelShowValueRow(int nTop, int nMain, int nValue, "
     "int bRefresh, int bVisible). Retorno void: los dos epilogos restauran pc "
     "sin definir r0, y el caller ignora el resultado."),
    ("layout_decision", "reused"),
    ("layout_evidence",
     "Reutiliza el layout existente sin cambiarlo. El unico campo que lee es "
     "+0x10 del objeto de sesion, y el read-back confirma que Ghidra ya lo "
     "tiene como nState int; el pool slot arm9_ov002.bss::0207f620 ya estaba "
     "tipado Ov002PanelSession *, y relocs.txt confirma que el literal en "
     "0x0205b6d8 apunta ahi (from:0x0205b6d8 kind:load to:0x0207f620). No "
     "aparece ningun offset nuevo: los otros valores que maneja son handles "
     "opacos de nodo que se pasan intactos a los callees."),
    ("types_applied_readback", "true"),
    ("types_evidence",
     "Read-back por direccion en arm9_ov002: los cinco parametros int con su "
     "almacenamiento, el campo nState int en +0x10 y nField0008 int en +0x08 de "
     "Ov002PanelSession, y el pool slot arm9_ov002.bss::0207f620 como "
     "Ov002PanelSession *. No se creo ni extendio ningun tipo porque no hacia "
     "falta."),
    ("transactions_closed", "true"),
    ("transactions_evidence",
     "Los dos scripts terminaron con SCRIPT COMPLETED SUCCESSFULLY sin dejar "
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
     "tools/audit_struct_sync.py sale con codigo 0 y no lista Ov002PanelSession "
     "con variantes en conflicto. Esta tanda no toco ningun tipo."),
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
