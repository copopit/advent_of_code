fn check_board(board: &Vec<Vec<(u32, bool)>>, draws: &Vec<u32>) -> bool {
    let mut board = board.clone();
    for draw in draws {
        for row in board.iter_mut() {
            for (i, (num, _)) in row.iter_mut().enumerate() {
                if num == draw {
                    row[i] = (*num, true);
                }
            }
        }
    }

    for row in board.iter() {
        for (_, found) in row.iter() {
            if !found {
                return false;
            }
        }
    }

    true
}

pub fn part_one(input: &str) -> Option<u32> {
    let inp = input.split('\n').collect::<Vec<&str>>();
    let draws = inp[0]
        .chars()
        .filter(|c| c != &',')
        .map(|c| c.to_digit(10).unwrap())
        .collect::<Vec<u32>>();

    let mut boards: Vec<Vec<Vec<(u32, bool)>>> = vec![];

    let mut board: Vec<Vec<(u32, bool)>> = Vec::with_capacity(5);

    for (i, row) in inp.iter().enumerate() {
        if i < 2 {
            continue;
        }
        if row.is_empty() || i == inp.len() - 1 {
            boards.push(board);
            board = Vec::with_capacity(5);
            continue;
        }

        board.push(
            row.split_whitespace()
                .map(|x| (u32::from_str_radix(x, 10).unwrap(), false))
                .collect(),
        );
    }

    println!("{:?}", boards);

    None
}

pub fn part_two(input: &str) -> Option<u32> {
    None
}

advent_of_code::main!(4);

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_one() {
        let result = part_one(&advent_of_code::template::read_file("examples", 4));
        assert_eq!(result, Some(4512));
    }

    #[test]
    fn test_part_two() {
        let result = part_two(&advent_of_code::template::read_file("examples", 4));
        assert_eq!(result, None);
    }
}
