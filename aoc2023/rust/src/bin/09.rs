advent_of_code::solution!(9);

fn rightmost_value(v: Vec<i32>) -> i32 {
    if v.iter().all(|x| *x == 0) {
        return 0;
    }
    let v_1 = v.windows(2).map(|val| val[1] - val[0]).collect::<Vec<_>>();
    v.last().unwrap() + rightmost_value(v_1)
}

fn leftmost_value(v: Vec<i32>) -> i32 {
    if v.iter().all(|x| *x == 0) {
        return 0;
    }
    let v_1 = v.windows(2).map(|val| val[1] - val[0]).collect::<Vec<_>>();
    v.first().unwrap() - leftmost_value(v_1)
}

pub fn part_one(input: &str) -> Option<i32> {
    Some(
        input
            .lines()
            .map(|line| {
                rightmost_value(
                    line.split_whitespace()
                        .map(|x| x.parse::<i32>().unwrap())
                        .collect::<Vec<i32>>(),
                )
            })
            .sum(),
    )
}

pub fn part_two(input: &str) -> Option<i32> {
    Some(
        input
            .lines()
            .map(|line| {
                leftmost_value(
                    line.split_whitespace()
                        .map(|x| x.parse::<i32>().unwrap())
                        .collect::<Vec<i32>>(),
                )
            })
            .sum(),
    )
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_one() {
        let result = part_one(&advent_of_code::template::read_file("examples", DAY));
        assert_eq!(result, Some(114));
    }

    #[test]
    fn test_part_two() {
        let result = part_two(&advent_of_code::template::read_file("examples", DAY));
        assert_eq!(result, Some(2));
    }
}
