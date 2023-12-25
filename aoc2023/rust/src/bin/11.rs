advent_of_code::solution!(11);

#[derive(Debug)]
struct Galaxy {
    j: usize,
    i: usize,
}

impl Galaxy {
    fn new(j: usize, i: usize) -> Self {
        Self { j, i }
    }
}

pub fn part_one(input: &str) -> Option<u32> {
    let mut galaxies: Vec<Galaxy> = Vec::new();

    let mut y_expansions: Vec<usize> = Vec::new();
    let mut x_expansions: Vec<usize> = Vec::new();

    let space = input
        .lines()
        .map(|row| {
            if row.chars().all(|c| c == '.') {
                y_expansions.push(y_expansions.last().unwrap_or(&0) + 1);
            } else {
                y_expansions.push(*y_expansions.last().unwrap_or(&0));
            }
            row.chars().collect::<Vec<_>>()
        })
        .collect::<Vec<_>>();

    for i in 0..space[0].len() {
        let mut found_galaxy = false;
        for j in 0..space.len() {
            if space[j][i] == '#' {
                found_galaxy = true;
                galaxies.push(Galaxy::new(i, j));
            }
        }

        if found_galaxy {
            x_expansions.push(*x_expansions.last().unwrap_or(&0));
        } else {
            x_expansions.push(*x_expansions.last().unwrap_or(&0) + 1);
        }
    }

    let mut sum = 0;
    for current in 0..galaxies.len() {
        for other in current + 1..galaxies.len() {
            let cur = &galaxies[current];
            let oth = &galaxies[other];

            let diff = (cur.i + y_expansions[cur.i]).abs_diff(oth.i + y_expansions[oth.i])
                + (cur.j + x_expansions[cur.j]).abs_diff(oth.j + x_expansions[oth.j]);

            sum += diff;
        }
    }

    Some(sum as u32)
}

pub fn part_two(input: &str) -> Option<u64> {
    let space_multiplier: usize = 999_999;
    let mut galaxies: Vec<Galaxy> = Vec::new();

    let mut y_expansions: Vec<usize> = Vec::new();
    let mut x_expansions: Vec<usize> = Vec::new();

    let space = input
        .lines()
        .map(|row| {
            if row.chars().all(|c| c == '.') {
                y_expansions.push(y_expansions.last().unwrap_or(&0) + space_multiplier);
            } else {
                y_expansions.push(*y_expansions.last().unwrap_or(&0));
            }
            row.chars().collect::<Vec<_>>()
        })
        .collect::<Vec<_>>();

    for i in 0..space[0].len() {
        let mut found_galaxy = false;
        for j in 0..space.len() {
            if space[j][i] == '#' {
                found_galaxy = true;
                galaxies.push(Galaxy::new(i, j));
            }
        }

        if found_galaxy {
            x_expansions.push(*x_expansions.last().unwrap_or(&0));
        } else {
            x_expansions.push(*x_expansions.last().unwrap_or(&0) + space_multiplier);
        }
    }

    let mut sum = 0;
    for current in 0..galaxies.len() {
        for other in current + 1..galaxies.len() {
            let cur = &galaxies[current];
            let oth = &galaxies[other];

            let diff = (cur.i + y_expansions[cur.i]).abs_diff(oth.i + y_expansions[oth.i])
                + (cur.j + x_expansions[cur.j]).abs_diff(oth.j + x_expansions[oth.j]);

            sum += diff;
        }
    }

    Some(sum as u64)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_one() {
        let result = part_one(&advent_of_code::template::read_file("examples", DAY));
        assert_eq!(result, Some(374));
    }

    #[test]
    fn test_part_two() {
        let result = part_two(&advent_of_code::template::read_file("examples", DAY));

        // assert_eq!(result, Some(374));
        // assert_eq!(result, Some(1030));
        assert_eq!(result, Some(8410));
    }
}
