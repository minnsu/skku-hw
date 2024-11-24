module M = Map.Make(String)

type t = (string list * Ast.expr) M.t

let add = M.add

let mem = M.mem

let find = M.find

let empty = M.empty
