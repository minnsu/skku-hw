let fibo n =
  let rec inner n a b =
    if n < 2 then n * a
    else inner (n-1) (a+b) a
  in
  inner n 1 0;;

module F = Format;;
let _ = F.printf "%d\n" (fibo 0) in
let _ = F.printf "%d\n" (fibo 1) in
let _ = F.printf "%d\n" (fibo 2) in
let _ = F.printf "%d\n" (fibo 3) in
let _ = F.printf "%d\n" (fibo 7) in
F.printf "%d\n" (fibo 10);;