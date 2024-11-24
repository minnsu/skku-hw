module M = Map.Make(String)

type t = Value.t M.t

let add = M.add

let mem = M.mem

let find = M.find

let empty = M.empty
