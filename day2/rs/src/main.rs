use std::fs;

fn repeats_m_times(s: &str, m: usize, n: usize) -> bool {
    if n % m != 0 { return false };
    
    let d = (n / m) as usize;
    let start = &s[..d];

    for i in (d..n).step_by(d) {
        let curr = &s[i..i + d];

        if start != curr {
            return false;
        }
    }
    
    return true;
}

fn main() {
    let part1: bool = false;

    let file_path = "../input.txt";
    let lines = fs::read_to_string(file_path).expect("can't read file");
    let mut invalid_id_sum: i64 = 0;

    if let Some(line) = lines.lines().next() {
        let ranges: Vec<&str> = line.split(',').collect();

        for range in ranges {
            if let Some((lstr, rstr)) = range.split_once('-') {
                let l: i64 = lstr.parse().expect("string could not be casted to int");
                let r: i64 = rstr.parse().expect("string could not be casted to int");

                for num in l..=r {
                    let s = num.to_string();
                    let n = s.len();

                    if part1 {
                        let lhs = &s[..n/2];
                        let rhs = &s[n/2..];
                        
                        if lhs == rhs {
                            invalid_id_sum += num;
                        }
                    } else {
                        for m in 2..=n {
                            if repeats_m_times(&s, m, n) {
                                invalid_id_sum += num;
                                break;
                            }   
                        }
                    }
                }
            }
        }
    }

    println!("{}", invalid_id_sum);

}
