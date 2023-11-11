pub fn str_to_vec_u32(input: &str) -> Vec<u32> {
    input
        .split('\n')
        .map(|x| x.parse::<u32>().unwrap())
        .collect::<Vec<u32>>()
}

pub fn str_to_vec(input: &str) -> Vec<&str> {
    input.split('\n').into_iter().collect::<Vec<&str>>()
}
