use std::{fs, vec};

fn merge_ranges(mut ranges: Vec<(i64, i64)> ) -> Vec<(i64, i64)> {
    // help from: https://www.geeksforgeeks.org/dsa/merging-intervals/

    ranges.sort_unstable();
    
    let mut iter = ranges.into_iter();
    let mut merged_ranges = vec![iter.next().unwrap()];

    for (curr_start, curr_end) in iter {

        let last = merged_ranges.last_mut().expect("could not get last element");
        let last_end = last.1;
        if curr_start <= last_end {
            last.1 = last_end.max(curr_end);
        } else {
            merged_ranges.push((curr_start, curr_end));
        }
    }

    merged_ranges
}

fn main() {
    let part1 = false;

    let file_path = "input.txt";
    let lines = fs::read_to_string(file_path).expect("can't read file");
    let mut is_range = true;
    let mut ranges = vec![];
    let mut num_fresh = 0;

    for line in lines.lines() {

        if line.is_empty() {
            is_range = false;
        } else if is_range {
            if let Some((lstr, rstr)) = line.split_once('-') {
                let l: i64 = lstr.parse().expect("string could not be casted to int");
                let r: i64 = rstr.parse().expect("string could not be casted to int");

                ranges.push((l, r));
            } else {
                println!("couldn't parse");
            }
        } else {
            if part1 {
                let num: i64 = line.parse().expect("string could not be casted to int");
    
                for &(l, r) in &ranges {
                    if l <= num && num <= r {
                        num_fresh += 1;
                        break;
                    }
                }
            }
        }
    }

    if !part1 {
        let merged_ranges = merge_ranges(ranges);
        
        for (l, r) in merged_ranges {
            num_fresh += r - l + 1;
        }
    }

    println!("{}", num_fresh);
}
