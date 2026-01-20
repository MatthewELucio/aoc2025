use { std::fs, std::collections::HashMap };

type Key = (usize, usize, Vec<u8>);
type Cache = HashMap<Key, u64>;

fn get_classical_num_splits(grid: &mut [Vec<u8>]) -> u64 {
    let mut num_splits = 0;

    for r in 1..grid.len() {
        if r == 0 {
            continue;
        }

        for c in 0..grid[0].len() {
            let ch = grid[r][c];
            if ch == b'^' {
                if grid[r - 1][c] == b'|' {
                    num_splits += 1;
                    grid[r][c - 1] = b'|';
                    grid[r][c + 1] = b'|';
                }
            } else if ch == b'.' && (grid[r - 1][c] == b'S' || grid[r - 1][c] == b'|') {
                grid[r][c] = b'|';
            }
        }
    }

    for row in grid.iter() {
        println!("{}", String::from_utf8_lossy(row));
    }

    num_splits
}

fn dfs(grid: &mut [Vec<u8>], r: usize, c: usize, is_split: bool, cache: &mut Cache) -> u64{
    if r == grid.len() {
        return 1;
    } 

    let row = grid[r].clone();
    let key: Key = (r, c, row);

    if !is_split && let Some(&num_splits) = cache.get(&key) {
        return num_splits;
    }

    let mut num_splits = 0;

    for c in 0..grid[0].len() {
        let ch = grid[r][c];
        if ch == b'^' {
            if grid[r - 1][c] == b'|' {
                grid[r][c - 1] = b'|';

                num_splits += dfs(grid, r + 1, c, true, cache);

                let mut tr = r;
                while tr < grid.len() && grid[tr][c - 1] == b'|'{
                    grid[tr][c - 1] = b'.';
                    tr += 1;
                }

                grid[r][c + 1] = b'|';

                num_splits += dfs(grid, r + 1, c, true, cache);
                let mut tr = r;
                while tr < grid.len() && grid[tr][c + 1] == b'|'{
                    grid[tr][c + 1] = b'.';
                    tr += 1;
                }
            }
        } else if ch == b'.' && (grid[r - 1][c] == b'S' || grid[r - 1][c] == b'|') {
            grid[r][c] = b'|';
            num_splits += dfs(grid, r + 1, c, false, cache);
        } 
    }

    cache.insert(key, num_splits);
    
    num_splits
}

fn get_quantum_num_splits(grid: &mut [Vec<u8>]) -> u64 {
    let mut cache = Cache::new();
    dfs(grid, 1, 0, false, &mut cache)
}

fn main() {
    let part1 = false;

    let file_path = "input.txt";
    let lines = fs::read_to_string(file_path).expect("can't read file");
    let mut grid: Vec<Vec<u8>> = lines.lines().map(|l| l.as_bytes().to_vec()).collect();
    
    let num_splits = if part1 {
        get_classical_num_splits(&mut grid)
    } else {
        get_quantum_num_splits(&mut grid)
    };

    dbg!(num_splits);
}
