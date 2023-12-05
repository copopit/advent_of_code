advent_of_code::solution!(4);

pub fn part_one(input: &str) -> Option<u32> {
    let tot = input
        .lines()
        .map(|line| {
            let pos = line.chars().position(|c| c == ':').unwrap();
            let numbers = line[pos + 1..]
                .split(" | ")
                .map(|nums| {
                    nums.split_whitespace()
                        .map(|n| n.parse::<u32>().unwrap())
                        .collect::<Vec<_>>()
                })
                .collect::<Vec<_>>();
            let winning_numbers =
                numbers[1].iter().filter(|x| numbers[0].contains(x)).count() as u32;

            if winning_numbers == 0 {
                0
            } else {
                (2 as u32).pow(winning_numbers - 1)
            }
        })
        .sum::<u32>();

    Some(tot)
}

#[derive(Debug)]
struct Card {
    index: usize,
    winning_numbers: usize,
    total: usize,
}

pub fn part_two(input: &str) -> Option<u32> {
    let mut cards = input
        .lines()
        .enumerate()
        .map(|(i, line)| {
            let pos = line.chars().position(|c| c == ':').unwrap();
            let numbers = line[pos + 2..]
                .split(" | ")
                .map(|nums| {
                    nums.split_whitespace()
                        .map(|n| n.parse::<u32>().unwrap())
                        .collect::<Vec<_>>()
                })
                .collect::<Vec<_>>();
            let winning_numbers = numbers[1].iter().filter(|x| numbers[0].contains(x)).count();

            return Card {
                index: i,
                winning_numbers: winning_numbers,
                total: 1,
            };
        })
        .collect::<Vec<Card>>();

    for i in 0..cards.len() {
        let Card {
            index: c_i,
            winning_numbers: w_n,
            total: c_tot,
        } = cards[i];
        for _ in 0..c_tot {
            for j in 1..=w_n {
                if c_i + j >= cards.len() {
                    break;
                }
                cards[c_i + j].total += 1;
            }
        }
    }

    Some(cards.iter().fold(0, |acc, x| acc + x.total as u32))
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_one() {
        let result = part_one(&advent_of_code::template::read_file("examples", DAY));
        assert_eq!(result, Some(13));
    }

    #[test]
    fn test_part_two() {
        let result = part_two(&advent_of_code::template::read_file("examples", DAY));
        assert_eq!(result, Some(30));
    }
}
