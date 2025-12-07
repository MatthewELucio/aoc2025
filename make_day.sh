echo "day $1"
cargo new day$1
cd day$1
touch day$1.cpp
aocdl -year 2025 -day $1
touch test.txt
cargo run
