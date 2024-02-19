use std::io::{self, Write, stdout};
use text_io::scan;
use termion::raw::{IntoRawMode, RawTerminal};
use termion::clear;

fn main(){
    print!("Enter field size (XxY) > ");
    io::stdout().flush().unwrap();
    let mut x: i32;
    let mut y: i32;
    scan!("{}x{}", x, y);

    if (x < 30) || (y < 30){
        print!("Your size less than 30x30, a you sure?(Yes/no) > ");
        io::stdout().flush().unwrap();
        loop{
            let mut less = String::new();
            io::stdin().read_line(&mut less).expect("Ошибка при чтении строки");
            let less_tr = less.trim();
            if (less_tr == "Yes") || (less_tr.is_empty()) || (less_tr == "yes"){
                break;
            }
            else if  (less_tr == "No") || (less_tr == "no"){
                x = 30;
                y = 30;
                break;
            }
            else {
                println!("Incorrect input")
            }
        }
    }

    loop {
        for i in 0..x {
            for j in 0..y {
                print!("#");
            }
            println!();
        }
        scan!("{}x{}", x, y);
    }
}
