advent_of_code::solution!(7);
use itertools::Itertools;
use std::collections::HashMap;

fn card_sum(cards: &str, part_2: bool) -> Vec<u32> {
    cards
        .chars()
        .map(|c| match c {
            'A' => 14,
            'K' => 13,
            'Q' => 12,
            'J' => {
                if part_2 {
                    1
                } else {
                    11
                }
            }
            'T' => 10,
            _ => c.to_digit(10).unwrap(),
        })
        .collect()
}

fn hand_strength(cards: &HashMap<char, usize>) -> u32 {
    if cards.len() == 1 {
        7
    } else if cards.len() == 2 {
        if cards.values().any(|&x| x == 4) {
            6
        } else {
            5
        }
    } else if cards.len() == 3 {
        if cards.values().any(|&x| x == 3) {
            4
        } else {
            3
        }
    } else if cards.len() == 4 {
        2
    } else {
        1
    }
}

#[derive(Debug)]
struct Hand {
    cards: HashMap<char, usize>,
    bid: u32,
    strength: u32,
    sum: Vec<u32>,
}

impl Hand {
    fn new_pt1(cards: &str, bid: u32) -> Self {
        let mut hash_cards: HashMap<char, usize> = HashMap::new();
        cards.chars().for_each(|c| {
            hash_cards.entry(c).and_modify(|x| *x += 1).or_insert(1);
        });

        Hand {
            cards: hash_cards.clone(),
            bid,
            strength: hand_strength(&hash_cards),
            sum: card_sum(cards, false),
        }
    }

    fn new_pt2(cards: &str, bid: u32) -> Self {
        let mut hash_cards: HashMap<char, usize> = HashMap::new();
        let mut jack_count = 0;
        cards.chars().for_each(|c| {
            if c != 'J' {
                hash_cards.entry(c).and_modify(|x| *x += 1).or_insert(1);
            } else {
                jack_count += 1;
            }
        });

        if jack_count == 5 {
            hash_cards.insert('J', jack_count);
        } else {
            if jack_count > 0 {
                let largest_count = hash_cards.iter().max_by(|a, b| a.1.cmp(&b.1)).unwrap();

                hash_cards
                    .entry(*largest_count.0)
                    .and_modify(|e| *e += jack_count)
                    .or_insert(jack_count);
            }
        }

        Hand {
            cards: hash_cards.clone(),
            bid,
            strength: hand_strength(&hash_cards),
            sum: card_sum(cards, true),
        }
    }

    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        if self.strength != other.strength {
            self.strength.cmp(&other.strength)
        } else {
            self.sum.cmp(&other.sum)
        }
    }
}

pub fn part_one(input: &str) -> Option<u32> {
    let hands = input
        .lines()
        .map(|line| {
            let mut it = line.split_whitespace();
            Hand::new_pt1(
                it.next().unwrap(),
                it.next().unwrap().parse::<u32>().unwrap(),
            )
        })
        .sorted_by(Hand::cmp)
        .collect::<Vec<Hand>>();

    let sum: u32 = hands
        .iter()
        .enumerate()
        .map(|(i, h)| h.bid * (i as u32 + 1))
        .sum();

    Some(sum)
}

pub fn part_two(input: &str) -> Option<u32> {
    let hands = input
        .lines()
        .map(|line| {
            let mut it = line.split_whitespace();
            Hand::new_pt2(
                it.next().unwrap(),
                it.next().unwrap().parse::<u32>().unwrap(),
            )
        })
        .sorted_by(Hand::cmp)
        .collect::<Vec<Hand>>();

    let sum: u32 = hands
        .iter()
        .enumerate()
        .map(|(i, h)| h.bid * (i as u32 + 1))
        .sum();

    Some(sum)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_one() {
        let result = part_one(&advent_of_code::template::read_file("examples", DAY));
        assert_eq!(result, Some(6440));
    }

    #[test]
    fn test_part_two() {
        let result = part_two(&advent_of_code::template::read_file("examples", DAY));
        assert_eq!(result, Some(5905));
    }
}
