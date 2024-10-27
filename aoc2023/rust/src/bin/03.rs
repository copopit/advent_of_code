advent_of_code::solution!(3);

fn get_row_num(line: &Vec<char>, j: usize) -> Option<u32> {
    if !line[j].is_digit(10) && !line[j - 1].is_digit(10) && !line[j + 1].is_digit(10) {
        return None;
    }

    let mut s_offset = j;
    let mut e_offset = j;
    let mut tot = 0;

    if !line[j].is_digit(10) {
        if j > 0 && line[j - 1].is_digit(10) {
            e_offset = j - 1;
            while s_offset > 0 && line[s_offset - 1].is_digit(10) {
                s_offset -= 1;
            }
            tot += line[s_offset..=e_offset]
                .iter()
                .collect::<String>()
                .parse::<u32>()
                .unwrap();

            s_offset = j;
            e_offset = j;
        }

        if j < line.len() - 1 && line[j + 1].is_digit(10) {
            s_offset = j + 1;
            while e_offset < line.len() - 1 && line[e_offset + 1].is_digit(10) {
                e_offset += 1;
            }
            tot += line[s_offset..=e_offset]
                .iter()
                .collect::<String>()
                .parse::<u32>()
                .unwrap();
        }
    } else {
        while s_offset > 0 && line[s_offset - 1].is_digit(10) {
            s_offset -= 1;
        }
        while e_offset < line.len() - 1 && line[e_offset + 1].is_digit(10) {
            e_offset += 1;
        }
        tot += line[s_offset..=e_offset]
            .iter()
            .collect::<String>()
            .parse::<u32>()
            .unwrap();
    }

    Some(tot)
}

fn is_symbol(c: &char) -> bool {
    !c.is_digit(10) && *c != '.'
}

pub fn part_one(input: &str) -> Option<u32> {
    let mut tot = 0;

    let lines = input
        .lines()
        .map(|l| l.chars().collect::<Vec<_>>())
        .collect::<Vec<_>>();

    for (i, line) in lines.iter().enumerate() {
        for (j, c) in line.iter().enumerate() {
            if is_symbol(c) {
                if i > 0 && i < lines.len() - 1 {
                    if let Some(n) = get_row_num(&lines[i - 1], j) {
                        tot += n;
                    }
                    if let Some(n) = get_row_num(&lines[i + 1], j) {
                        tot += n;
                    }
                }
                if let Some(n) = get_row_num(line, j) {
                    tot += n;
                }
            }
        }
    }

    Some(tot)
}

pub fn part_two(input: &str) -> Option<u32> {
    let lines = input
        .lines()
        .map(|l| l.chars().collect::<Vec<_>>())
        .collect::<Vec<_>>();

    None
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_one() {
        let result = part_one(&advent_of_code::template::read_file("examples", DAY));
        assert_eq!(result, Some(4361));
    }

    #[test]
    fn test_part_two() {
        let result = part_two(&advent_of_code::template::read_file("examples", DAY));
        assert_eq!(result, None);
    }
}
