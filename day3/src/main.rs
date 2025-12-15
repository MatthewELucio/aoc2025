use std::fs;

fn get_max_dig_in_range(line: &str, j: usize, k: usize, n: usize) -> (u32, usize) {
    let mut max = '0';
    let bytes = line.as_bytes();
    let mut ret_j = 0;

    for i in j..(n - k) {
        let ch = bytes[i] as char;

        if ch > max {
            max = ch;
            ret_j = i + 1;
        }
    }
    let dig = max.to_digit(10).unwrap();
    (dig, ret_j)
}

fn get_max_joltage(line: &str, num_batteries: usize) -> u64 {
    let mut j = 0;
    let n = line.len();
    let mut max_joltage: u64 = 0;


    for k in (0..num_batteries).rev() {
        let (dig, ret_j) = get_max_dig_in_range(line, j, k, n);
        j = ret_j;
        max_joltage = 10 * max_joltage + (dig as u64);
    }

    max_joltage
}

fn main() {
    let part1 = false;

    let file_path = "input.txt";
    let lines = fs::read_to_string(file_path).expect("can't read file");
    let mut total_joltage = 0;

    for line in lines.lines() {
        let max_joltage=  if part1 {
            get_max_joltage(line, 2)
        } else {
            get_max_joltage(line, 12)
        };
        total_joltage += max_joltage;
    }
    
    println!("{}", total_joltage);
}
