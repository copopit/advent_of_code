advent_of_code::solution!(10);

enum Pipe {
    NS,
    EW,
    NE,
    SE,
    SW,
    NW,
}

impl Pipe {
    fn is_valid(&self, other: Pipe) -> bool {
        match *self {
            Pipe::NS => match other {},
        }
    }
}

pub fn part_one(input: &str) -> Option<u32> {
    let matrix = input
        .lines()
        .map(|line| line.chars().collect::<Vec<_>>())
        .collect::<Vec<_>>();

    let mut start = (0, 0);

    for (i, l) in matrix.iter().enumerate() {
        for (j, c) in l.iter().enumerate() {
            if c == &'S' {
                start = (i, j);
                break;
            }
        }
        if start != (0, 0) {
            break;
        }
    }

    None
}

pub fn part_two(input: &str) -> Option<u32> {
    None
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_one() {
        let result = part_one(&advent_of_code::template::read_file("examples", DAY));
        assert_eq!(result, None);
    }

    #[test]
    fn test_part_two() {
        let result = part_two(&advent_of_code::template::read_file("examples", DAY));
        assert_eq!(result, None);
    }
}
