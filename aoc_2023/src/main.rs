mod input_parser;
mod solvers;

use std::error::Error;
use std::{env, process};

struct Config {
    file_path: String,
    date: usize,
    puzzle_part: solvers::PuzzlePart,
}

impl Config {
    pub fn build(mut args: impl Iterator<Item = String>) -> Result<Config, &'static str> {
        // The first value in the return value of env::args is the name of the program, so ignore
        args.next();

        let file_path = match args.next() {
            Some(arg) => arg,
            None => return Err("Input a file path."),
        };

        let date = match args.next() {
            Some(arg) => arg.parse::<usize>().unwrap(),
            None => return Err("Input the date to solve, e.g to solve Day 1 enter 1."),
        };

        let puzzle_part = match args.next() {
            Some(arg) => arg.parse::<solvers::PuzzlePart>().unwrap(),
            None => return Err("Specify which part to solve, P1 or P2"),
        };

        Ok(Config {
            file_path,
            date,
            puzzle_part,
        })
    }
}

fn main() -> Result<(), Box<dyn Error>> {
    let config = Config::build(env::args()).unwrap_or_else(|err| {
        eprintln!("Problem parsing arguments: {err}");
        process::exit(1);
    });

    let input_vec: Vec<String> = input_parser::parse_input_file(config.file_path)?;

    let solution = match config.date {
        1 => solvers::day01_solver(&input_vec, config.puzzle_part),
        // 2 => solvers::day02_solver(&input_vec);
        // 3 => solvers::day03_solver(&input_vec);
        // 4 => solvers::day04_solver(&input_vec);
        // 5 => solvers::day05_solver(&input_vec);
        _ => panic!("No solver for specified date."),
    };

    match solution {
        Ok(sol) => {
            println!("The final solution is: {sol}.");
            Ok(())
        }
        Err(e) => panic!("No solution found: {e}"),
    }
}
