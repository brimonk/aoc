use std::io;

fn main()
{
    let x: i32 = 0;
    let y: i32 = 0;

    println!("Hello World!");
    println!("{} {}", x, y);

    let lines = io::stdin().lines();
    let line = lines[0].unwrap();

    println!("{}", line);
}
