let rec fold3 f a b_list c_list d_list =
  match b_list with
  | [] -> a
  | _ ->
    let tmp = f a (List.hd b_list) (List.hd c_list) (List.hd d_list) in
    fold3 f tmp (List.tl b_list) (List.tl c_list) (List.tl d_list)
  ;;

module F = Format;;
let _ = F.printf "%d\n" (fold3 (fun a b c d -> a + b + c + d) 10 [33;67;12;33] [10;23;84;57] [11;55;23;58]) in
let _ = F.printf "%d\n" (fold3 (fun a b c d -> (-a) + b + c + d) 4 [11;63;-45;22] [75;123;-44;1] [55;24;20;3]) in
let _ = F.printf "%d\n" (fold3 (fun a b c d -> a * b * c * d) 55 [] [] []) in
let _ = F.printf "%d\n" (fold3 (fun a b c d -> (a * b * c + d) mod 7) 33 [12;33] [10;7] [5;12]) in
let _ = F.printf "%d\n" (fold3 (fun a b c d -> if b then a + c else a + d) 34 [true;false;false;true] [12;3;4;77] [11;23;6;100]) in
F.printf "%d\n" (fold3 (fun a b c d -> if b then a else c + d) 55 [true;true;false;false;true] [111;63;88;123;98] [0;23;778;34;6]);;