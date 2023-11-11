use advent_of_code::utils::str_to_vec;

pub fn part_one(input: &str) -> Option<u32> {
    let (mut hori, mut vert): (u32, u32) = (0, 0);
    str_to_vec(input).iter().for_each(|line| {
        let s = line.split(' ').collect::<Vec<&str>>();
        match s[0] {
            "forward" => hori += s[1].parse::<u32>().unwrap(),
            "down" => vert += s[1].parse::<u32>().unwrap(),
            "up" => vert -= s[1].parse::<u32>().unwrap(),
            _ => {}
        };
    });

    Some(hori * vert)
}

pub fn part_two(input: &str) -> Option<u64> {
    let (mut total_hori, mut aim, mut depth): (u64, u64, u64) = (0, 0, 0);
    str_to_vec(input).iter().for_each(|line| {
        let s = line.split(' ').collect::<Vec<&str>>();
        match s[0] {
            "forward" => {
                let hori = s[1].parse::<u64>().unwrap();
                total_hori += hori;
                depth += aim * hori;
            }
            "down" => aim += s[1].parse::<u64>().unwrap(),
            "up" => aim -= s[1].parse::<u64>().unwrap(),
            _ => {}
        };
    });

    println!("{:?} -> {:?} -> {:?}", total_hori, aim, depth);

    Some(total_hori * depth)
}

advent_of_code::main!(2);

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_one() {
        let result = part_one(&advent_of_code::template::read_file("examples", 2));
        assert_eq!(result, Some(150));
    }

    #[test]
    fn test_part_two() {
        let result = part_two(&advent_of_code::template::read_file("examples", 2));
        assert_eq!(result, Some(900));
    }
}
