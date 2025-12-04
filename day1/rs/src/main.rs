// use std::env;
use std::fs;

fn p1turn(dial: i32, is_left: bool, distance: i32) -> i32 {
    const M: i32 = 100;
    if is_left {
        let res = (dial - distance) % M;
        if res < 0 {
            res + M
        } else {
            res
        }
    } else {
        (dial + distance) % M
    }
}

fn p2turn(dial: i32, is_left: bool, distance: i32) -> (i32, i32) {
    const M: i32 = 100;
    if is_left {
        let res = (dial - distance) % M;
        let mut num_clicks = -(dial - distance) / M;
        if dial != 0 && res < 0 {
            num_clicks += 1;
        }
        // println!("{} {} {}", dial, distance, res);
        if res < 0 {
            (res + M, num_clicks)
        } else {
            (res, num_clicks)
        }
    } else {
        let mut num_clicks = (dial + distance) / M;
        if ((dial + distance) % M) == 0 {num_clicks -= 1};
        ((dial + distance) % M, num_clicks)
    }
    
}

fn main() {
    let part1: bool = false;

    let file_path = "../input.txt";
    let lines = fs::read_to_string(file_path).expect("can't read file");

    let mut dial = 50;
    let mut num_dial_zero = 0;

    for line in lines.lines() {
        let dir = &line[0..1];
        let distance: i32 = (&line[1..]).trim().parse().expect("string could not be casted to int");

        if part1 {
            dial = p1turn(dial, dir == "L", distance);

            if dial == 0 {
                num_dial_zero += 1;
            }
        } else {
            let (new_dial, num_clicks) = p2turn(dial, dir == "L", distance);
            dial = new_dial;

            if dial == 0 {
                num_dial_zero += 1;
            }

            num_dial_zero += num_clicks;
            // println!("{} {} {} {} {}", dir, distance, dial, num_clicks, num_dial_zero);
        }
    }

    println!("{}", num_dial_zero);
}
