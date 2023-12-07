use std::error::Error;
use std::str::FromStr;

pub enum PuzzlePart {
    P1,
    P2,
}

impl FromStr for PuzzlePart {
    type Err = &'static str;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        // Parse the string and construct a PuzzlePart instance
        match s {
            "P1" => Ok(PuzzlePart::P1),
            "P2" => Ok(PuzzlePart::P2), // Example with a field
            _ => Err("Failed to parse PuzzlePart entry."),
        }
    }
}

fn find_calibration_value(input: &str) -> Result<u32, &'static str> {
    let mut first_ascii_digit: Option<char> = None;
    let mut last_ascii_digit: Option<char> = None;

    for character in input.chars() {
        if character.is_ascii_digit() {
            if first_ascii_digit.is_none() {
                first_ascii_digit = Some(character);
            }
            last_ascii_digit = Some(character);
        }
    }

    if let (Some(first_digit), Some(last_digit)) = (
        first_ascii_digit.and_then(|c| c.to_digit(10)),
        last_ascii_digit.and_then(|c| c.to_digit(10)),
    ) {
        let calibration_value = first_digit * 10 + last_digit;
        Ok(calibration_value)
    } else {
        Err("First or last digit not found.")
    }
}

fn day01_p1_solver(input_vec: &[String]) -> Result<u32, Box<dyn Error>> {
    let mut calibration_values: Vec<u32> = vec![];

    for input in input_vec.iter() {
        let cv = find_calibration_value(input.as_str())?;
        calibration_values.push(cv);
    }

    if calibration_values.is_empty() {
        return Err("Calibration values vector is empty.".into());
    }
    let sum: u32 = calibration_values.iter().sum();
    Ok(sum)
}

fn day01_p2_solver(input_vec: &[String]) -> Result<u32, Box<dyn Error>> {
    let mut sanitized_input_vec: Vec<String> = vec![];

    for input in input_vec.iter() {
        let sani_input = input
            .replace("ten", "t10n")
            .replace("eleven", "e11n")
            .replace("twelve", "t12e")
            .replace("thirteen", "t13n")
            .replace("fourteen", "f14n")
            .replace("fifteen", "f15n")
            .replace("sixteen", "s16n")
            .replace("seventeen", "s17n")
            .replace("eighteen", "e18n")
            .replace("nineteen", "n19n")
            .replace("twenty", "t2")
            .replace("thirty", "t3")
            .replace("forty", "f4")
            .replace("fifty", "f5")
            .replace("sixty", "s6")
            .replace("seventy", "s7")
            .replace("eighty", "e8")
            .replace("ninety", "n9")
            .replace("one", "o1e")
            .replace("two", "t2o")
            .replace("three", "t3e")
            .replace("four", "f4r")
            .replace("five", "f5e")
            .replace("six", "s6i")
            .replace("seven", "s7n")
            .replace("eight", "e8t")
            .replace("nine", "n9e");

        sanitized_input_vec.push(sani_input);
    }
    return day01_p1_solver(&sanitized_input_vec);
}

pub fn day01_solver(input_vec: &[String], puzzle_part: PuzzlePart) -> Result<u32, Box<dyn Error>> {
    match puzzle_part {
        PuzzlePart::P1 => day01_p1_solver(input_vec),
        PuzzlePart::P2 => day01_p2_solver(input_vec),
    }
}

#[cfg(test)]
mod tests {
    #[test]
    fn test_find_calibration_value() {
        use super::*;
        let input = "1abc2";
        assert_eq!(Ok(12), find_calibration_value(input));

        let input = "pqr3stu8vwx";
        assert_eq!(Ok(38), find_calibration_value(input));

        let input = "a1b2c3d4e5f";
        assert_eq!(Ok(15), find_calibration_value(input));

        let input = "treb7uchet";
        assert_eq!(Ok(77), find_calibration_value(input));
    }

    #[test]
    fn test_day01_p1_solver() {
        use super::*;
        let input_vec: Vec<String> = vec![
            "1abc2".to_string(),
            "pqr3stu8vwx".to_string(),
            "a1b2c3d4e5f".to_string(),
            "treb7uchet".to_string(),
        ];
        assert_eq!(142, day01_p1_solver(&input_vec).unwrap());
    }

    #[test]
    fn test_day01_p2_solver() {
        use super::*;
        let input_vec: Vec<String> = vec![
            "two1nine".to_string(),         // 29
            "eightwothree".to_string(),     // 83
            "abcone2threexyz".to_string(),  // 13
            "xtwone3four".to_string(),      // 24
            "4nineeightseven2".to_string(), // 42
            "zoneight234".to_string(),      // 14
            "7pqrstsixteen".to_string(),    // 76
        ];
        assert_eq!(281, day01_p2_solver(&input_vec).unwrap());
    }
}
