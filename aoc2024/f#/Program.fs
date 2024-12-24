open Year2024Day01

let printResult (part1: Option<int>, part2: Option<int>) =
    printfn "Part 1: %A" part1
    printfn "Part 2: %A" part2

[<EntryPoint>]
let main argv =
    let initials = Year2024Day02.countSalutes ">->->-<-<"
    printfn "%A" initials
    0
// match argv[0] with
// | "1" -> printResult (Year2024Day01.solve ())
// | _ -> printfn "Unknown day"

// 0
