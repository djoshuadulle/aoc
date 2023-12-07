use std::error::Error;
use std::fs::File;
use std::io::{BufRead, BufReader};
use std::path::PathBuf;

pub fn parse_input_file(file_path: String) -> Result<Vec<String>, Box<dyn Error>> {
    // Create a path to the input file
    let path = PathBuf::from(file_path);
    // Open the path in read-only mode, returns `io::Result<File>`,
    // then pass to a BufReader to create an iterator over each line
    let file_iter = match File::open(path.as_path()) {
        Ok(file) => BufReader::new(file).lines(),
        Err(why) => panic!("Couldn't open {}: {}", path.display(), why),
    };

    let mut input_vec: Vec<String> = vec![];
    for line in file_iter {
        input_vec.push(line.expect("Error parsing input file line."));
    }

    Ok(input_vec)
}
