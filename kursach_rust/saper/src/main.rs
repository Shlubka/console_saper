use std::io::{self, Write, stdout};
use text_io::scan;
use termion::raw::{IntoRawMode, RawTerminal};
use termion::clear;


/*enter_move (move: char) -> (i32, i32){

}*/

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
        let mut stdout = stdout();
        let mut stdout = stdout.lock().into_raw_mode().unwrap();
        for c in std::io::stdin().keys() {
        match c.unwrap() {
            // Если пользователь нажимает 'q', выходим из цикла
            termion::event::Key::Char('q') => break,
            _ => {}
        }
    }
    drop(stdout); // Отключаем "сырой" режим
    let mut stdout = stdout.into_raw_mode().unwrap().into_inner();

    }
}
