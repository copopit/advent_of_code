advent_of_code::solution!(1);
use regex::Regex;

pub fn part_one(input: &str) -> Option<u32> {
    let total = input
        .lines()
        .map(|line| {
            let s: String = line.chars().filter(|c| c.is_numeric()).collect();

            return s.chars().nth(0).unwrap().to_digit(10).unwrap() * 10
                + s.chars().last().unwrap().to_digit(10).unwrap();
        })
        .sum();

    Some(total)
}

fn strnum_to_num(s: &str) -> Option<u32> {
    match s {
        "one" => Some(1),
        "two" => Some(2),
        "three" => Some(3),
        "four" => Some(4),
        "five" => Some(5),
        "six" => Some(6),
        "seven" => Some(7),
        "eight" => Some(8),
        "nine" => Some(9),
        _ => None,
    }
}

pub fn part_two(input: &str) -> Option<u32> {
    let res = input
        .lines()
        .map(|l| {
            let mut res: Vec<u32> = vec![];
            for (i, c) in l.chars().enumerate() {
                if c.is_numeric() {
                    res.push(c.to_digit(10).unwrap());
                } else if i >= 2 {
                    let mut s = &l[i - 2..=i];
                    if let Some(n) = strnum_to_num(s) {
                        res.push(n);
                        continue;
                    }
                    if i >= 3 {
                        s = &l[i - 3..=i];
                        if let Some(n) = strnum_to_num(s) {
                            res.push(n);
                            continue;
                        }
                    }
                    if i >= 4 {
                        s = &l[i - 4..=i];
                        if let Some(n) = strnum_to_num(s) {
                            res.push(n);
                        }
                    }
                }
            }
            res[0] * 10 + res[res.len() - 1]
        })
        .sum();

    Some(res)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_one() {
        let result = part_one(&advent_of_code::template::read_file("examples", DAY));
        assert_eq!(result, Some(142));
    }

    #[test]
    fn test_part_two() {
        let result = part_two(&advent_of_code::template::read_file("examples", DAY));
        assert_eq!(result, Some(281));
    }
}
