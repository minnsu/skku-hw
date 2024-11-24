let is_prime n =
  if n = 1 then false
  else if n <= 3 then true
  else if n mod 2 = 0 then false
  else
    let sqrted = int_of_float (sqrt (float_of_int n)) in
    let rec inner m =
      if m > sqrted then true
      else if n mod m = 0 then false
      else inner (m+1)
    in
  inner 3
  ;;

let goldbach_list_limit lower upper min_prime =
  let rec loop target upper result_list =
    if target >= upper then result_list
    else
      let rec find x =
        let y = target - x in
        if x >= y then (-1, (-1, -1))
        else if is_prime x && is_prime y then
          (target, (x, y))
        else
          find (x+1)
        in
      let goldbach_pair = find 2 in
      let _, (x, y) = goldbach_pair in
      if x < min_prime then loop (target + 1) upper result_list
      else loop (target + 1) upper (result_list @ [goldbach_pair])
  in
  loop lower upper [];;

module F = Format;;

let print_tup_list t_li = 
  let rec print_tup_subli sub_t_li first = 
    match sub_t_li with
    | [] -> F.printf "]\n"
    | h::t ->
      let cpx, (pr1, pr2) = h in
      if first then
        F.printf "(%d, (%d, %d))" cpx  pr1 pr2
      else
        F.printf "; (%d, (%d, %d))" cpx pr1 pr2;
      print_tup_subli t false;
    in
    F.printf "[";
    print_tup_subli t_li true
    ;;

let _ = print_tup_list (goldbach_list_limit 9 20 5) in
let _ = print_tup_list (goldbach_list_limit 25 70 10) in
let _ = print_tup_list (goldbach_list_limit 100 100 100) in
let _ = print_tup_list (goldbach_list_limit 100 200 19) in
let _ = print_tup_list (goldbach_list_limit 50 500 20) in
print_tup_list (goldbach_list_limit 1 2000 50);;