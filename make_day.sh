echo "day $1"
mkdir day$1
cd day$1
touch day$1.cpp
touch input.txt
touch test.txt
cargo new rs
cd rs
cargo run