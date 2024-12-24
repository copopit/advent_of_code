module Year2024Day01

let example = [| "3   4"; "4   3"; "2   5"; "1   3"; "3   9"; "3   3" |]

let getInput = System.IO.File.ReadAllLines "./Inputs/day01.txt"

let part1: Option<int> =
    let left, right =
        getInput
        |> Array.map (fun x ->
            let parts = x.Split("   ") |> Array.map int
            parts.[0], parts.[1])
        |> Array.unzip

    let left = Array.sort left
    let right = Array.sort right

    Some(Array.zip left right |> Array.map (fun (l, r) -> (r - l) |> abs) |> Array.sum)

let part2: Option<int> =
    let left, right =
        getInput
        |> Array.map (fun x ->
            let parts = x.Split("   ") |> Array.map int
            parts.[0], parts.[1])
        |> Array.unzip

    let rightCounts =
        right
        |> Array.fold (fun acc x -> acc |> Map.add x ((Map.tryFind x acc |> Option.defaultValue 0) + 1)) Map.empty

    left
    |> Array.map (fun x -> x * (Map.tryFind x rightCounts |> Option.defaultValue 0))
    |> Array.sum
    |> Some

let solve () = (part1, part2)
