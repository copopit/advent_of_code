module Year2024Day02

let example =
    [| "7 6 4 2 1"
       "1 2 7 8 9"
       "9 7 6 2 1"
       "1 3 2 4 5"
       "8 6 4 4 1"
       "1 3 6 7 9" |]

let getInput = System.IO.File.ReadAllLines "./Inputs/day02.txt"

let handleSubArray (subArray: int[]) =
    subArray
    |> Array.windowed 2
    |> Array.fold
        (fun (acc1, isDescending) window ->
            match window with
            | [| a; b |] when a - b >= -3 && a - b <= 0 -> (true, true)
            | [| a; b |] when a - b >= 0 && a - b <= 3 -> (true, false)
            | _ -> (acc1, isDescending))
        (true, false)

let part1 () : Option<int> =
    // let a =
    //     getInput
    //     |> Array.map (fun x -> x.Split(" ") |> Array.map int)
    //     |> Array.mapi (fun i x -> if i < )
    //     |> Array.sum
let part2 () : Option<int> = None

let solve () = (part1, part2)
