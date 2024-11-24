let phi m =
  let rec gcd n m = 
    if m = 0 then n
    else gcd m (n mod m)
  in
  
  let rec check target result =
    if target = 0 then result
    else if gcd m target = 1 then check (target-1) (result + 1)
    else check (target-1) result
    in
  check (m-1) 0;;

module F = Format;;
let _ = F.printf "%d\n" (phi 4) in
let _ = F.printf "%d\n" (phi 9) in
let _ = F.printf "%d\n" (phi 10) in
let _ = F.printf "%d\n" (phi 17) in
F.printf "%d\n" (phi 30);;