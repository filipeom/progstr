let () =
  if Array.length Sys.argv < 4 then
    Format.printf "Usage: %s <length> <fill> <empty> <percent>@." Sys.argv.(0)

let () =
  let len = int_of_string Sys.argv.(1) in
  let fill = Sys.argv.(2).[0] in
  let empty = Sys.argv.(3).[0] in
  let percent = int_of_string Sys.argv.(4) in
  let i = len * percent / 100 in
  for _ = 0 to i - 1 do
    print_char fill
  done;
  for _ = i to len - 1 do
    print_char empty
  done