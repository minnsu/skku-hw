module F = Format
open Ast
open Value
open Interpreter
    
let%test _ = 
  try
  let ast =  (Prog ([], (Add (Id "x", Num 1)))) in
  interp ast = NumV 5 
  with Failure msg -> msg = "Free identifier: x"

let%test _ = 
  try
  let ast =  (Prog ([(FunDef ("x", [], (Add (Id "x", Num 1))))], (Call ("x", [])))) in
  interp ast = NumV 5 
  with Failure msg -> msg = "Free identifier: x"

let%test _ = 
  try
    let ast =  (Prog ([(FunDef ("x", ["x";"y"], (Add (Id "x", Num 1))))], (Call ("x", [])))) in
  interp ast = NumV 5 
  with Failure msg -> msg = "The number of arguments of x mismatched: Required: 2, Actual: 0"

let%test _ = 
  try
    let ast =  (Prog ([(FunDef ("x", ["x";"y"], (Add (Id "x", Num 1))))], (Call ("x", [Num 1])))) in
  interp ast = NumV 5 
  with Failure msg -> msg = "The number of arguments of x mismatched: Required: 2, Actual: 1"

let%test _ = 
  let ast =  (Prog ([(FunDef ("x", [], (Add (Num 5, Num 9))))], (Call ("x", [])))) in
  interp ast = NumV 14 

let%test _ = 
  let ast = (Prog ([(FunDef ("x", ["x"], (Add (Id "x", Num 1))))], (Call ("x", [Num 3])))) in 
  interp ast = NumV 4 

let%test _ = 
  let ast = (Prog ([(FunDef ("x", ["x"; "y"], (Add (Id "x", Id "y"))))], (Call ("x", [Num 3; Num 4])))) in 
  interp ast = NumV 7 

let%test _ = 
  let ast = (Prog ([(FunDef ("x", ["x"; "y"], (Sub (Id "x", Id "y"))))], (Call ("x", [Num 10; Num 5])))) in 
  interp ast = NumV 5 

let%test _ = 
  let ast = (Prog ([(FunDef ("x", ["x"; "y"], (Add (Id "x", Id "y")))); (FunDef ("x2", ["x"; "y"], (Sub(Id "x", Id "y"))))], (Call ("x", [Num 3; Num 4])))) in 
  interp ast = NumV 7 

let%test _ = 
  let ast = (Prog ([], (Add (Add ((Num 5, Num 18)), Num 30)))) in
  interp ast = NumV 53 

let%test _ = 
  let ast = (Prog ([], (Sub (Add ((Num 50, Num 18)), Num 3)))) in
  interp ast = NumV 65 

let%test _ = 
  let ast = (Prog ([], (Add (Add ((Num 1, Num 2)), Num (-3))))) in
  interp ast = NumV 0 

let%test _ = 
  let ast = (Prog ([], (LetIn (("x"), (Num 5), (Add (Num 3, Id "x"))) ))) in 
  interp ast = NumV 8 

let%test _ = 
  try
  let ast = (Prog ([], (LetIn (("x"), (Num 5), (Add (Num 3, Id "z"))) ))) in 
  interp ast = NumV 8 
  with Failure msg -> msg = "Free identifier: z"

let%test _ =
  try
  let ast =  (Prog ([(FunDef ("x", ["x";"y"], (Add (Id "x", Num 1))))], (Call ("y", [])))) in
  interp ast = NumV 5
  with Failure msg -> msg = "Undefined function: y"