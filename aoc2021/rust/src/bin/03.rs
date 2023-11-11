fn str_input_to_binary_u32_vec(input: &str) -> Vec<u32> {
    input
        .split('\n')
        .map(|e| u32::from_str_radix(e, 2).unwrap())
        .collect()
}

pub fn part_one(input: &str) -> Option<u32> {
    let bitlen = input.chars().take_while(|c| *c != '\n').count() as u32 - 1;
    let inp = str_input_to_binary_u32_vec(input);
    let mask: u32 = (1 << (bitlen + 1)) - 1; // 0b1111 1111 1111

    let gamma = (0..=bitlen).rev().fold(0, |acc: u32, pos| {
        if inp.iter().filter(|&&b| b & 1 << pos > 0).count() >= inp.len() / 2 {
            acc | 1 << pos
        } else {
            acc
        }
    });

    Some(gamma * (mask ^ gamma))
}

fn partition_vec_at_pos(input: &Vec<u32>, pos: u32) -> (Vec<u32>, Vec<u32>) {
    let (ones, zeros): (Vec<u32>, Vec<u32>) = input.iter().partition(|&&val| val & 1 << pos > 0);

    if ones.len() < zeros.len() {
        (zeros, ones)
    } else {
        (ones, zeros)
    }
}

pub fn part_two(input: &str) -> Option<u32> {
    let bitlen = input.chars().take_while(|c| *c != '\n').count() as u32 - 1;
    let (mut o2, mut co2): (Vec<u32>, Vec<u32>) =
        partition_vec_at_pos(&str_input_to_binary_u32_vec(input), bitlen);

    for pos in (0..bitlen).rev() {
        if o2.len() > 1 {
            (o2, _) = partition_vec_at_pos(&o2, pos);
        }
        if co2.len() > 1 {
            (_, co2) = partition_vec_at_pos(&co2, pos);
        }

        if o2.len() == 1 && co2.len() == 1 {
            return Some(o2[0] * co2[0]);
        }
    }

    None
}

advent_of_code::main!(3);

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_one() {
        let result = part_one(&advent_of_code::template::read_file("examples", 3));
        assert_eq!(result, Some(198));
    }

    #[test]
    fn test_part_two() {
        let result = part_two(&advent_of_code::template::read_file("examples", 3));
        assert_eq!(result, Some(230));
    }
}
