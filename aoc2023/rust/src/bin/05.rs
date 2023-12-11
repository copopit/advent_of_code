advent_of_code::solution!(5);
use std::ops::RangeInclusive;

use itertools::Itertools;

#[derive(Debug)]
struct AlmonacMap {
    dest: u64,
    source: u64,
    range: u64,
}

impl AlmonacMap {
    fn new(dest: u64, source: u64, range: u64) -> Self {
        AlmonacMap {
            dest,
            source,
            range,
        }
    }

    fn in_range(&self, n: u64) -> bool {
        n >= self.source && n <= self.range + self.source
    }

    fn delta(&self, n: u64) -> u64 {
        self.dest + n - self.source
    }
}

impl FromIterator<u64> for AlmonacMap {
    fn from_iter<I: IntoIterator<Item = u64>>(iter: I) -> Self {
        let mut iter = iter.into_iter();
        let dest = iter.next().unwrap();
        let source = iter.next().unwrap();
        let range = iter.next().unwrap() - 1;

        AlmonacMap {
            dest,
            source,
            range,
        }
    }
}

pub fn part_one(input: &str) -> Option<u32> {
    let mut inp_iter = input.split("\n\n");

    let seeds = inp_iter
        .next()
        .unwrap()
        .split(": ")
        .nth(1)
        .unwrap()
        .split_whitespace()
        .map(|n| n.parse::<u64>().unwrap())
        .collect::<Vec<_>>();

    let mappings = inp_iter
        .map(|step| {
            step.split(":\n")
                .nth(1)
                .unwrap()
                .split("\n")
                .map(|line| {
                    line.split_whitespace()
                        .map(|n| n.parse::<u64>().unwrap())
                        .collect::<AlmonacMap>()
                })
                .collect::<Vec<_>>()
        })
        .collect::<Vec<_>>();

    let mut location: u64 = u64::MAX;

    for seed in seeds.iter() {
        let mut mapped_val = *seed;
        for map in mappings.iter() {
            for m in map.iter() {
                if m.in_range(mapped_val) {
                    mapped_val = m.delta(mapped_val);
                    break;
                }
            }
        }
        if mapped_val < location {
            location = mapped_val;
        }
    }

    Some(location as u32)
}

#[derive(Debug, Clone)]
struct Seed {
    source: u64,
    range: u64,
}

impl Seed {
    fn new(source: u64, range: u64) -> Self {
        Seed { source, range }
    }

    fn in_range(&self, map: &AlmonacMap) -> bool {
        self.source >= map.source && self.source <= map.range + map.source
    }

    fn overlapping_range(&self, map: &AlmonacMap) -> bool {
        self.source <= map.source && self.source + self.range >= map.source
            || self.source >= map.source && self.source <= map.source + map.range
            || self.source <= map.source && self.source + self.range >= map.source + map.range
    }

    fn full_range(&self) -> RangeInclusive<u64> {
        self.source..=self.source + self.range
    }

    fn split_range(&self, map: &AlmonacMap) -> (Option<Seed>, Option<Seed>, Option<Seed>) {
        let mut lower = None;
        let mut upper = None;
        let mut middle = None;

        if self.source < map.source {
            lower = Some(Seed {
                source: self.source,
                range: map.source - self.source,
            });
        }

        if self.source >= map.source && self.source + self.range <= map.source + map.range {
            middle = Some(Seed {
                source: self.source,
                range: self.range,
            });
        }

        if self.source + self.range > map.source + map.range {
            upper = Some(Seed {
                source: map.source + map.range + 1,
                range: self.source + self.range - (map.source + map.range),
            });
        }

        (lower, middle, upper)
    }

    fn get_range(&self, map: &AlmonacMap) -> Seed {
        let s_d = map.dest + self.source - map.source;
        let diff = if s_d >= self.source {
            s_d - self.source
        } else {
            0
        };
        if self.range <= map.range {
            Seed {
                source: s_d,
                range: if diff < self.range {
                    self.range - diff
                } else {
                    0
                },
            }
        } else {
            Seed {
                source: s_d,
                range: if diff < map.range {
                    map.range - diff
                } else {
                    0
                },
            }
        }
    }
}

fn smallest_range(seed: Seed, mappings: &Vec<Vec<AlmonacMap>>, it: usize) -> Seed {
    if it >= mappings.len() {
        seed
    } else {
        let (mut lower, mut middle, mut upper): (Option<Seed>, Option<Seed>, Option<Seed>) =
            (None, None, None);
        for m in mappings[it] {
            if seed.overlapping_range(&m) {
                let (l, m, u) = seed.split_range(&m);
                if l.is_some() {
                    match lower {
                        Some(s) => {
                            if l.as_ref().unwrap().source < s.source {
                                lower = l;
                            }
                        }
                        None => lower = Some(smallest_range(l.unwrap(), mappings, 0)),
                    }
                }
                if m.is_some() {
                    match middle {
                        Some(s) => {
                            if m.as_ref().unwrap().source < s.source {
                                middle = m;
                            }
                        }
                        None => middle = Some(smallest_range(m.unwrap(), mappings, 0)),
                    }
                }
                if u.is_some() {
                    match upper {
                        Some(s) => {
                            if u.as_ref().unwrap().source < s.source {
                                upper = u;
                            }
                        }
                        None => upper = Some(smallest_range(u.unwrap(), mappings, 0)),
                    }
                }
            }
        }

        if lower.is_some() {}
    }
}

pub fn part_two(input: &str) -> Option<u32> {
    let mut inp_iter = input.split("\n\n");

    let seeds = inp_iter
        .next()
        .unwrap()
        .split(": ")
        .nth(1)
        .unwrap()
        .split_whitespace()
        .tuple_windows()
        .step_by(2)
        .map(|(s, r)| Seed {
            source: s.parse::<u64>().unwrap(),
            range: r.parse::<u64>().unwrap(),
        })
        .collect::<Vec<_>>();

    let mappings = inp_iter
        .map(|step| {
            step.split(":\n")
                .nth(1)
                .unwrap()
                .split("\n")
                .map(|line| {
                    line.split_whitespace()
                        .map(|n| n.parse::<u64>().unwrap())
                        .collect::<AlmonacMap>()
                })
                .collect::<Vec<_>>()
        })
        .collect::<Vec<_>>();

    let mut filtered_seeds: Vec<u64> = Vec::new();

    for seed in seeds.iter() {
        let mut mapped_val: Vec<Option<Seed>> = vec![
            None,
            Some(Seed {
                source: seed.source,
                range: seed.range,
            }),
            None,
        ];
        for map in mappings.iter() {
            for m in map.iter() {
                if mapped_val[1].as_ref().unwrap().in_range(m) {
                    if let Some(lower) = mapped_val[1].as_ref().unwrap().some_lowerbound(m) {
                        mapped_val[0] = Some(lower);
                    }
                    if let Some(upper) = mapped_val[1].as_ref().unwrap().some_upperbound(m) {
                        mapped_val[2] = Some(upper);
                    }
                    mapped_val[1] = Some(mapped_val[1].as_ref().unwrap().get_range(m));
                    println!("{:?}", mapped_val);
                }
            }
        }

        for val in mapped_val.iter() {
            match val {
                Some(v) => v.full_range().for_each(|x| {
                    if !filtered_seeds.contains(&x) {
                        filtered_seeds.push(x)
                    }
                }),
                None => (),
            }
        }
    }

    println!("{:?}", filtered_seeds);

    let mut location: u64 = u64::MAX;

    for seed in filtered_seeds.iter() {
        let mut mapped_val = *seed;
        for map in mappings.iter() {
            for m in map.iter() {
                if m.in_range(mapped_val) {
                    mapped_val = m.delta(mapped_val);
                    break;
                }
            }
        }
        if mapped_val < location {
            location = mapped_val;
            println!("{} -> {}", seed, location)
        }
    }

    Some(0)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_part_one() {
        let result = part_one(&advent_of_code::template::read_file("examples", DAY));
        assert_eq!(result, Some(35));
    }

    #[test]
    fn test_part_two() {
        let result = part_two(&advent_of_code::template::read_file("examples", DAY));
        assert_eq!(result, Some(46));
    }
}
