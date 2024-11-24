module F = Format

type expr = Num of int
  | Add of expr * expr
  | Sub of expr * expr
  | Id of string
  | LetIn of string * expr * expr
  | Call of string * expr list
type fundef = FunDef of string * string list * expr
type prog = Prog of fundef list * expr

let rec pp_expr fmt e = 
  match e with
  | Num n -> F.fprintf fmt "%d" n
  | Add (e1, e2) -> F.fprintf fmt "%a + %a" pp_expr e1 pp_expr e2
  | Sub (e1, e2) -> F.fprintf fmt "%a - %a" pp_expr e1 pp_expr e2
  | Id x -> F.fprintf fmt "%s" x
  | LetIn (x, e1, e2) -> F.fprintf fmt "let %s = %a in %a" x pp_expr e1 pp_expr e2
  | Call (x, el) -> F.fprintf fmt "%s(%a)" x 
      (F.pp_print_list ~pp_sep:(fun fmt () -> F.fprintf fmt ", ") 
        (fun fmt e -> F.fprintf fmt "%a" pp_expr e))
      el

let pp_fundef fmt d = 
  match d with
  | FunDef (x, pl, e) -> F.fprintf fmt "def %s %a = %a endef" x 
      (F.pp_print_list ~pp_sep:(fun fmt () -> F.fprintf fmt " ")
        (fun fmt p -> F.fprintf fmt "%s" p)) 
      pl pp_expr e

let pp fmt p = 
  match p with
  | Prog (dl, e) -> F.fprintf fmt "%a\n%a" 
      (F.pp_print_list ~pp_sep:(fun fmt () -> F.fprintf fmt "\n")
        (fun fmt d -> F.fprintf fmt "%a" pp_fundef d))
      dl pp_expr e

let rec pp_ast_expr fmt e = 
  match e with
  | Num n -> F.fprintf fmt "(Num %d)" n
  | Add (e1, e2) -> F.fprintf fmt "(Add %a, %a)" pp_ast_expr e1 pp_ast_expr e2
  | Sub (e1, e2) -> F.fprintf fmt "(Sub %a, %a)" pp_ast_expr e1 pp_ast_expr e2
  | Id x -> F.fprintf fmt "(Id %s)" x
  | LetIn (x, e1, e2) -> F.fprintf fmt "(LetIn %s, %a, %a)" x pp_ast_expr e1 pp_ast_expr e2
  | Call (x, el) -> F.fprintf fmt "(Call %s, [%a])" x 
      (F.pp_print_list ~pp_sep:(fun fmt () -> F.fprintf fmt "; ") 
        (fun fmt e -> F.fprintf fmt "%a" pp_ast_expr e))
      el

let pp_ast_fundef fmt d = 
  match d with
  | FunDef (x, pl, e) -> F.fprintf fmt "(FunDef %s, [%a], %a)" x 
      (F.pp_print_list ~pp_sep:(fun fmt () -> F.fprintf fmt "; ")
        (fun fmt p -> F.fprintf fmt "%s" p)) 
      pl pp_ast_expr e

let pp_ast fmt p = 
  match p with
  | Prog (dl, e) -> F.fprintf fmt "(Prog [%a], %a)" 
      (F.pp_print_list ~pp_sep:(fun fmt () -> F.fprintf fmt "; ")
        (fun fmt d -> F.fprintf fmt "%a" pp_ast_fundef d))
      dl pp_ast_expr e
