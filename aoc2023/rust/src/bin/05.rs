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

    fn full_range(&self) -> RangeInclusive<u64> {
        self.source..=self.source + self.range
    }

    fn some_upperbound(&self, map: &AlmonacMap) -> Option<Seed> {
        if self.source + self.range > map.range + map.source {
            Some(Seed {
                source: map.range + map.source + 1,
                range: self.source + self.range - (map.range + map.source),
            })
        } else {
            None
        }
    }

    fn some_lowerbound(&self, map: &AlmonacMap) -> Option<Seed> {
        if self.source < map.source && self.source + self.range > map.source {
            Some(Seed {
                source: self.source,
                range: map.source - self.source,
            })
        } else {
            None
        }
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

pub fn part_two(input: &str) -> Option<u32> {
    let mut inp_iter = input.split("\n\n");

    let mut seeds = inp_iter
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
