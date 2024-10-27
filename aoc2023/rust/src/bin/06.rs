advent_of_code::solution!(6);

fn lower_start(time: u64, dist: u64) -> u64 {
    for speed in 1..time {
        if (time - speed) * speed > dist {
            return speed;
        }
    }
    0
}

fn upper_start(time: u64, dist: u64) -> u64 {
    for speed in (1..time).rev() {
        if (time - speed) * speed > dist {
            return speed;
        }
    }
    0
}

fn delta(time: u64, dist: u64) -> u64 {
    upper_start(time, dist) - lower_start(time, dist) + 1
}

pub fn part_one(input: &str) -> Option<u32> {
    let t = input
        .lines()
        .map(|line| {
            line.split(":")
                .nth(1)
                .unwrap()
                .split_whitespace()
                .map(|n| n.parse::<u64>().unwrap())
                .collect::<Vec<_>>()
        })
        .collect::<Vec<_>>();

    let mut sum = 1;

    for i in 0..t[0].len() {
        sum *= delta(t[0][i], t[1][i]);
    }

    Some(sum as u32)
}

pub fn part_two(input: &str) -> Option<u32> {
    let t = input
        .lines()
        .map(|line| {
            line.split(":")
                .nth(1)
                .unwrap()
                .split_whitespace()
                .collect::<String>()
                .parse::<u64>()
                .unwrap()
        })
        .collect::<Vec<_>>();

    Some(delta(t[0], t[1]) as u32)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_one() {
        let result = part_one(&advent_of_code::template::read_file("examples", DAY));
        assert_eq!(result, Some(288));
    }

    #[test]
    fn test_part_two() {
        let result = part_two(&advent_of_code::template::read_file("examples", DAY));
        assert_eq!(result, None);
    }
}
