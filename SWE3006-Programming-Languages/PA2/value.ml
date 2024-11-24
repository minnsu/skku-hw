module F = Format

type t = NumV of int

let pp fmt (NumV n) = F.fprintf fmt "%d" n
