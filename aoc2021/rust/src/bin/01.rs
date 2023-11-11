fn str_to_vec_u32(input: &str) -> Vec<u32> {
    input
        .split('\n')
        .map(|x| x.parse::<u32>().unwrap())
        .collect::<Vec<u32>>()
}

pub fn part_one(input: &str) -> Option<u32> {
    let res = str_to_vec_u32(input)
        .windows(2)
        .filter(|vals| vals[0] < vals[1])
        .count();

    Some(res as u32)
}

pub fn part_two(input: &str) -> Option<u32> {
    let res = str_to_vec_u32(input)
        .windows(3)
        .map(|slice| slice.iter().sum::<u32>())
        .collect::<Vec<u32>>()
        .windows(2)
        .filter(|vals| vals[0] < vals[1])
        .count();

    Some(res as u32)
}

advent_of_code::main!(1);

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_one() {
        let result = part_one(&advent_of_code::template::read_file("examples", 1));
        assert_eq!(result, Some(7));
    }

    #[test]
    fn test_part_two() {
        let result = part_two(&advent_of_code::template::read_file("examples", 1));
        assert_eq!(result, Some(5));
    }
}
