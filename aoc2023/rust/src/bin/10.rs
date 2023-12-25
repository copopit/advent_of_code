advent_of_code::solution!(10);

#[derive(Debug)]
enum Dir {
    N,
    S,
    E,
    W,
}

#[derive(Debug, PartialEq, Eq)]
struct Tile {
    pipe: char,
    visited: bool,
}

impl Tile {
    fn is_connected(&self, other: &Tile, position: Dir) -> bool {
        if other.visited {
            return false;
        }
        match position {
            Dir::N => self.check_north(other),
            Dir::S => self.check_south(other),
            Dir::E => self.check_east(other),
            Dir::W => self.check_west(other),
        }
    }

    fn check_north(&self, other: &Tile) -> bool {
        match self.pipe {
            '|' | 'L' | 'J' | 'S' => match other.pipe {
                '|' => true,
                'F' => true,
                '7' => true,
                _ => false,
            },
            _ => false,
        }
    }

    fn check_south(&self, other: &Tile) -> bool {
        match self.pipe {
            '|' | 'F' | '7' | 'S' => match other.pipe {
                '|' => true,
                'L' => true,
                'J' => true,
                _ => false,
            },
            _ => false,
        }
    }

    fn check_east(&self, other: &Tile) -> bool {
        match self.pipe {
            '-' | 'L' | 'F' | 'S' => match other.pipe {
                '-' => true,
                '7' => true,
                'J' => true,
                _ => false,
            },
            _ => false,
        }
    }

    fn check_west(&self, other: &Tile) -> bool {
        match self.pipe {
            '-' | 'J' | '7' | 'S' => match other.pipe {
                '-' => true,
                'L' => true,
                'F' => true,
                _ => false,
            },
            _ => false,
        }
    }
}

pub fn part_one(input: &str) -> Option<u32> {
    let mut start = (0, 0);
    let mut grid = input
        .lines()
        .enumerate()
        .map(|(i, line)| {
            line.chars()
                .enumerate()
                .map(|(j, c)| {
                    if c == 'S' {
                        start = (i, j);
                    }

                    if c == '.' {
                        Tile {
                            pipe: c,
                            visited: true,
                        }
                    } else {
                        Tile {
                            pipe: c,
                            visited: false,
                        }
                    }
                })
                .collect::<Vec<Tile>>()
        })
        .collect::<Vec<_>>();

    grid[start.0][start.1].visited = true;

    let mut walk = start;
    let mut len = 0;

    loop {
        let cur = &grid[walk.0][walk.1];

        if walk.1 > 0 && cur.is_connected(&grid[walk.0][walk.1 - 1], Dir::W) {
            walk.1 -= 1;
        } else if walk.1 < grid.len() - 1 && cur.is_connected(&grid[walk.0][walk.1 + 1], Dir::E) {
            walk.1 += 1;
        } else if walk.0 < grid.len() - 1 && cur.is_connected(&grid[walk.0 + 1][walk.1], Dir::S) {
            walk.0 += 1;
        } else if walk.0 > 0 && cur.is_connected(&grid[walk.0 - 1][walk.1], Dir::N) {
            walk.0 -= 1;
        }

        let is_same = cur == &grid[walk.0][walk.1];

        grid[walk.0][walk.1].visited = true;

        if is_same {
            break;
        }
        len += 1;
    }

    println!("{:?}", len);

    Some(if len % 2 == 0 { len / 2 } else { len / 2 + 1 })
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
        assert_eq!(result, Some(8));
    }

    #[test]
    fn test_part_two() {
        let result = part_two(&advent_of_code::template::read_file("examples", DAY));
        assert_eq!(result, None);
    }
}
