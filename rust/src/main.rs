use std::io;

fn main(){
    let mut a_str = String::new();
    let mut b_str = String::new();
    let mut c_str = String::new();

    loop {
    println!("Enter number a");

    match io::stdin().read_line(&mut a_str){
        Ok(_) => {},
        Err(e) => println!("\n Error {e}"),
    }

    println!("Enter number b");

    match io::stdin().read_line(&mut b_str){
        Ok(_) => {},
        Err(e) => println!("\n Error {e}"),
    }

    println!("Enter number c");

    match io::stdin().read_line(&mut c_str){
        Ok(_) => {},
        Err(e) => println!("\n Error {e}"),
    }


    let a: f64 = a_str.trim().parse().unwrap();
    let b: f64 = b_str.trim().parse().unwrap();
    let c: f64 = c_str.trim().parse().unwrap();
    print!("a = {a}, b = {b}, c = {c}\n");

    let d: f64 = (b*b) - 4.0 * (a * c);

    if d > 0.0{
        let x1 = ((-b) + d.sqrt()) / (2.0 * a);
        let x2 = ((-b) - d.sqrt()) / (2.0 * a);
        print!("x1 = {x1}, x2 = {x2}\n");
    }
    else if d == 0.0{
        let x1 = ((-b) + d.sqrt()) / (2.0 * a);
        print!("x1 = {x1}\n");
    }

    print!("d = {d}")

}
}
