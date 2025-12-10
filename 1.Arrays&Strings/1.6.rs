// String Compression: Implement a method to perform basic string compression
// using the counts of repeated characters. For example, the string aabcccccaaa
// would become a2blc5a3. If the "compressed" string would not become smaller
// than the original string, your method should return the original string. You
// can assume the string has only uppercase and lowercase letters (a - z).

use googletest::prelude::*;

fn string_compression(s: &str) -> String {
  let mut ret = String::new();
  if s.len() == 0 {
    return ret;
  }

  let mut count = 1;
  let mut prev = s.chars().next().unwrap();
  for c in s.chars().skip(1) {
    if c == prev {
      count += 1;
    } else {
      ret.push_str(&format!("{}{}", prev, count));
      count = 1;
    }
    prev = c;
  }
  ret.push_str(&format!("{}{}", prev, count));

  if ret.len() >= s.len() {
    return s.to_string();
  }
  ret
}

#[gtest]
fn string_compression_assertions() {
  expect_eq!(string_compression("aabcccccaaa"), "a2b1c5a3");
  expect_eq!(string_compression("a"), "a");
  expect_eq!(string_compression("aa"), "aa");
  expect_eq!(string_compression("aab"), "aab");
  expect_eq!(string_compression("aabccccccccccaaa"), "a2b1c10a3");
  expect_eq!(string_compression("aaab"), "aaab");
  expect_eq!(string_compression("aabbccdd"), "aabbccdd");
}
