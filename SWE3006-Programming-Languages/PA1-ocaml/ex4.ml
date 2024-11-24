let merge (a : int list) (b : int list) =
  let sorted = List.sort compare (a @ b) in 
  List.rev sorted;;

module F = Format;;
let rec print_list li = 
  let rec print_e sub_li first =
    match sub_li with
    | [] -> F.print_string "]\n"
    | h::t ->
      if first then
        F.printf "%d" h
      else F.printf ";%d" h;
      print_e t false;
  in
  let _ = F.printf "[" in
  print_e li true;;

let _ = print_list (merge [3;2;1] [5;4]) in
let _ = print_list (merge [5;3] [5;2]) in
let _ = print_list (merge [4;2] []) in
let _ = print_list (merge [] [2;1]) in
let _ = print_list (merge [] []) in
let _ = print_list (merge [0;0;0;0] [0;0;0;0]) in
let _ = print_list (merge [4;3;-2] [9;7;7]) in
print_list (merge [-2;-999] []);;