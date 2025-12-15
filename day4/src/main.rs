use std::fs;

#[allow(non_snake_case)]
fn get_neighbors(grid: &Vec<Vec<u8>>, r: usize, c: usize, R: usize, C: usize) -> usize {
    let mut neighbors = 0;

    for dr in -1..=1 {
        for dc in -1..=1 {
            if dr == 0 && dc == 0 {
                continue;
            }

            let nr = r as isize + dr;
            let nc = c as isize + dc;

            if 0 <= nr && nr < R as isize && 0 <= nc && nc < C as isize {
                if grid[nr as usize][nc as usize] == b'@' {
                    neighbors += 1;
                }
            }
        }
    }

    neighbors
}

fn get_rolls(grid: &mut Vec<Vec<u8>>) -> usize {
    let mut rolls = 0;

    #[allow(non_snake_case)]
    let R: usize = grid.len();
    #[allow(non_snake_case)]
    let C = grid[0].len();

    let mut accessed_coords = vec![];
    let mut old_x_coords = vec![];

    for r in 0..R {
        for c in 0..C {
            if grid[r][c] == b'.' {
                continue;
            }

            if grid[r][c] == b'x' {
                old_x_coords.push((r, c));
                continue;
            }

            let neighbors = get_neighbors(grid, r, c, R, C);
            if neighbors < 4 {
                rolls += 1;
                accessed_coords.push((r, c));
            }
        }
    }

    for (r, c) in accessed_coords {
        grid[r][c] = b'x';
    }

    for (r, c) in old_x_coords {
        grid[r][c] = b'.';
    }

    rolls
}

fn main() {
    let part1 = false;

    let file_path = "input.txt";
    let lines = fs::read_to_string(file_path).expect("can't read file");
    let mut grid: Vec<Vec<u8>> = lines.lines().map(|l| l.as_bytes().to_vec()).collect();
    
    if part1 {
        let rolls = get_rolls(&mut grid);
        println!("{}", rolls);
    } else {
        let mut total_rolls = 0;
        for row in &grid {
            println!("{}", String::from_utf8_lossy(row));
        }
        println!();

        let mut rolls = get_rolls(&mut grid);
        while rolls > 0 {
            for row in &grid {
                println!("{}", String::from_utf8_lossy(row));
            }
            println!();
            total_rolls += rolls;

            rolls = get_rolls(&mut grid);
        }

        println!("{}", total_rolls);
    }
}
