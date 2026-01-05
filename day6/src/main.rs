use std::{fs};

#[derive(Debug, PartialEq, Clone, Copy)]
enum Op {
    Add,
    Mul,
}

fn get_grand_total(all_nums: Vec<Vec<u64>>, all_chars: Vec<&str>) -> u64{
    let mut grand_total = 0;

    let n = all_nums[0].len();
    let m = all_nums.len();
    
    for (i, char) in all_chars.iter().enumerate().take(n) {
        let curr_op = if char == &"+" {Op::Add } else {Op::Mul};
        let mut total = if curr_op == Op::Add {0} else {1};
        for row in all_nums.iter().take(m) {
            let num = row[i];
            if curr_op == Op::Add {
                total += num;
            } else if curr_op == Op::Mul {
                total *= num;
            }
        }
        grand_total += total;
    }

    grand_total
}

fn get_grand_total_p2(all_lines: Vec<&str>) -> u64 {
    let mut grand_total = 0;

    let mut curr_op = Op::Add;
    let mut problem_total = 0;

    for j in 0..all_lines[0].len() {
        let mut is_empty_col = true;
        let mut col_num: u64 = 0;
        
        for &row in all_lines.iter() {
            let ch = row.as_bytes()[j];
            if ch.is_ascii_whitespace() {
                continue;
            } else if ch == b'+' {
                curr_op = Op::Add;
                problem_total = 0;
                continue;
            } else if ch == b'*' {
                curr_op = Op::Mul;
                problem_total = 1;
                continue;
            } else {
                is_empty_col = false;
                let num = ch - b'0';
                col_num = 10 * col_num + num as u64;
            }
        }

        if is_empty_col {
            grand_total += problem_total;
            continue;
        }

        if curr_op == Op::Add {
            problem_total += col_num;
        } else if curr_op == Op::Mul {
            problem_total *= col_num;
        }
    }
    
    grand_total
}

fn main() {
    let part1 = false;

    let file_path = "input.txt";
    let lines = fs::read_to_string(file_path).expect("can't read file");

    let mut all_lines = vec![];
    for line in lines.lines() {
        all_lines.push(line);
    }
    
    let grand_total = if part1 {
        let mut all_nums = vec![];
        
        for line in all_lines.iter().take(all_lines.len() - 1) {
            let nums: Vec<u64> = line.split_whitespace().map(|s| s.parse().expect("not a number")).collect();
            all_nums.push(nums);
        }
        
        let all_chars: Vec<&str> = all_lines.last().expect("couldn't get last").split_whitespace().collect();
        
        get_grand_total(all_nums, all_chars)
    } else {
        get_grand_total_p2(all_lines)
    };

    println!("{}", grand_total);

}
