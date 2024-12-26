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
    let initial = subArray[0] - subArray[1]
    let isDescending = if initial < 0 then true else false

    subArray
    |> Array.windowed 2
    |> Array.fold
        (fun (acc1, isDescending) window ->
            let result = window[0] - window[1]

            match result with
            | x when x < 0 && (isDescending = None || isDescending = Some true) -> (true, Some true)
            | x when x > 0 && (isDescending = None || isDescending = Some false) -> (true, Some false)
            | _ -> (acc1, isDescending))
        (false, None)
    |> fst

let part1 () : Option<int> =
    // let a =
    //     getInput
    //     |> Array.map (fun x -> x.Split(" ") |> Array.map int)
    //     |> Array.mapi (fun i x -> if i < )
    //     |> Array.sum
    None

let part2 () : Option<int> = None

let solve () = (part1, part2)
