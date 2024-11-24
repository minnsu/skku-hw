module F = Format

let rec interp_expr (e: Ast.expr) (g: FStore.t) (s: Store.t) : Value.t = 
 (* Implement this function *)
  match e with
  | Num x -> NumV x
  | Add (e1, e2) ->
    (let v1, v2 = (interp_expr e1 g s), (interp_expr e2 g s) in
    match v1, v2 with
    | NumV n1, NumV n2 -> NumV (n1 + n2))
  | Sub (e1, e2) ->
    (let v1, v2 = (interp_expr e1 g s), (interp_expr e2 g s) in
    match v1, v2 with
    | NumV n1, NumV n2 -> NumV (n1 - n2))
  | Id var -> 
    if Store.M.mem var s then
      Store.M.find var s
    else
      failwith (F.sprintf "Free identifier: %s" var)
  | LetIn (var, e1, e2) ->
    let new_s = Store.M.add var (interp_expr e1 g s) s in
    interp_expr e2 g new_s
  | Call (f_name, para_list1) ->
    if FStore.M.mem f_name g then
      let (para_list2, body) = FStore.M.find f_name g in
      let def_len, act_len = List.length para_list2, List.length para_list1 in
      if def_len != act_len then
        failwith (F.sprintf "The number of arguments of %s mismatched: Required: %d, Actual: %d" f_name def_len act_len)
      else
        let new_s = List.fold_right2 (fun expr name store -> Store.M.add name (interp_expr expr g s) store) para_list1 para_list2 Store.M.empty in
        interp_expr body g new_s
    else
      failwith (F.sprintf "Undefined function: %s" f_name)

let interp_fundef (d: Ast.fundef) (g: FStore.t) : FStore.t = 
 (* Implement this function *)
  match d with
  | FunDef (f_name, para_list, body) ->
  FStore.M.add f_name (para_list, body) g

let interp (p: Ast.prog) : Value.t = 
 (* Implement this function *)
  match p with
  | Prog (def_list, expr) ->
    let fs = List.fold_right interp_fundef def_list FStore.M.empty in
    interp_expr expr fs Store.M.empty
