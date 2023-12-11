advent_of_code::solution!(8);
use itertools::Itertools;
use num::integer::lcm;
use std::collections::HashMap;

pub fn part_one(input: &str) -> Option<u32> {
    let mut it = input.split("\n\n");
    let mut path_map: HashMap<&str, (&str, &str)> = HashMap::new();

    let dir = it.next().unwrap().chars().collect::<Vec<char>>();

    it.next().unwrap().lines().for_each(|l| {
        let mut split = l.split(" = ");
        let k = split.next().unwrap();
        let v = split.next().unwrap();
        path_map.insert(
            k,
            v[1..v.len() - 1]
                .split(", ")
                .next_tuple::<(&str, &str)>()
                .unwrap(),
        );
    });

    let mut walk = path_map.get_key_value("AAA").unwrap();
    let mut index = 0;
    while walk.0 != &"ZZZ" {
        walk = match dir[index % dir.len()] {
            'R' => path_map.get_key_value(walk.1 .1).unwrap(),
            'L' => path_map.get_key_value(walk.1 .0).unwrap(),
            _ => unreachable!(),
        };
        index += 1;
    }

    Some(index as u32)
}

pub fn part_two(input: &str) -> Option<usize> {
    let mut it = input.split("\n\n");
    let mut path_map: HashMap<&str, (&str, &str)> = HashMap::new();

    let dir = it.next().unwrap().chars().collect::<Vec<char>>();

    it.next().unwrap().lines().for_each(|l| {
        let mut split = l.split(" = ");
        let k = split.next().unwrap();
        let v = split.next().unwrap();
        path_map.insert(
            k,
            v[1..v.len() - 1]
                .split(", ")
                .next_tuple::<(&str, &str)>()
                .unwrap(),
        );
    });

    path_map
        .iter()
        .filter_map(|(k, _)| match k.chars().nth(2) {
            Some('A') => {
                let mut walk = path_map.get_key_value(k).unwrap();
                let mut index = 0;
                while walk.0.chars().nth(2).unwrap() != 'Z' {
                    walk = match dir[index % dir.len()] {
                        'R' => path_map.get_key_value(walk.1 .1).unwrap(),
                        'L' => path_map.get_key_value(walk.1 .0).unwrap(),
                        _ => unreachable!(),
                    };
                    index += 1;
                }
                Some(index)
            }
            _ => None,
        })
        .reduce(|a, b| lcm(a, b))
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_one() {
        let result = part_one(&advent_of_code::template::read_file("examples", DAY));
        assert_eq!(result, Some(2));
    }

    #[test]
    fn test_part_two() {
        let result = part_two(&advent_of_code::template::read_file("examples", DAY));
        assert_eq!(result, Some(6));
    }
}
