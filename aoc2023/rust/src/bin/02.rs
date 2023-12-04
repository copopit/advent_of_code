advent_of_code::solution!(2);

enum Color {
    Red(u32),
    Green(u32),
    Blue(u32),
}

impl Color {
    fn new(color: &str, num: u32) -> Self {
        match color {
            "red" => Color::Red(num),
            "green" => Color::Green(num),
            "blue" => Color::Blue(num),
            _ => panic!("Invalid color"),
        }
    }
    fn cmp(&self, other: &Color) -> bool {
        match self {
            Color::Red(n) => match other {
                Color::Red(m) => n <= m,
                _ => false,
            },
            Color::Green(n) => match other {
                Color::Green(m) => n <= m,
                _ => false,
            },
            Color::Blue(n) => match other {
                Color::Blue(m) => n <= m,
                _ => false,
            },
        }
    }
    fn is_smaller(&self) -> bool {
        match self {
            Color::Red(n) => *n <= 12,
            Color::Green(n) => *n <= 13,
            Color::Blue(n) => *n <= 14,
        }
    }

    fn val(&self) -> u32 {
        match self {
            Color::Red(n) => *n,
            Color::Green(n) => *n,
            Color::Blue(n) => *n,
        }
    }
}

pub fn part_one(input: &str) -> Option<u32> {
    let tot = input
        .lines()
        .map(|line| {
            let pos = line.chars().position(|c| c == ':').unwrap();
            return !line[pos + 1..]
                .split("; ")
                .map(|r| {
                    !r.split(", ")
                        .map(|draw| {
                            let tmp = draw.split_whitespace().collect::<Vec<_>>();
                            let num = tmp[0].parse::<u32>().unwrap();
                            let color = tmp[1];

                            return Color::new(color, num).is_smaller();
                        })
                        .collect::<Vec<_>>()
                        .contains(&false)
                })
                .collect::<Vec<_>>()
                .contains(&false);
        })
        .enumerate()
        .fold(
            0,
            |acc: u32, (i, val)| if val { acc + 1 + i as u32 } else { acc },
        );

    Some(tot)
}

pub fn part_two(input: &str) -> Option<u32> {
    let tot: u32 = input
        .lines()
        .map(|line| {
            let pos = line.chars().position(|c| c == ':').unwrap();
            let (mut red, mut green, mut blue): (Color, Color, Color) =
                (Color::Red(0), Color::Green(0), Color::Blue(0));
            line[pos + 1..].split("; ").for_each(|r| {
                r.split(", ").for_each(|draw| {
                    let tmp = draw.split_whitespace().collect::<Vec<_>>();
                    let num = tmp[0].parse::<u32>().unwrap();
                    let color = tmp[1];

                    let col = Color::new(color, num);

                    if red.cmp(&col) {
                        red = col;
                    } else if green.cmp(&col) {
                        green = col;
                    } else if blue.cmp(&col) {
                        blue = col;
                    }
                })
            });

            return red.val() * green.val() * blue.val();
        })
        .sum();

    Some(tot)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_one() {
        let result = part_one(&advent_of_code::template::read_file("examples", DAY));
        assert_eq!(result, Some(8));
    }

    #[test]
    fn test_part_two() {
        let result = part_two(&advent_of_code::template::read_file("examples", DAY));
        assert_eq!(result, Some(2286));
    }
}
