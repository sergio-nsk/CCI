// URLify: Write a method to replace all spaces in a string with '%20'. You may
// assume that the string has sufficient space at the end to hold the additional
// characters, and that you are given the "true" length of the string. (Note: If
// implementing in Java, please use a character array so that you can perform
// this operation in place.)
//
// EXAMPLE Input:
//  "Mr John Smith", 13
// Output:
//  "Mr%20John%20Smith"

use googletest::prelude::*;

fn encode_spaces(url: &str) -> String {
  let cnt = url.chars().filter(|&ch| ch == ' ').count();
  if cnt == 0 {
    return url.to_string();
  }

  let mut ret = url.to_string();

  let chars: &mut Vec<u8> = unsafe { ret.as_mut_vec() };
  chars.resize(chars.len() + cnt * 2, 0);

  let mut to = chars.len() - 1;
  let mut from = to - cnt * 2;
  while to != from {
    let mut ch = chars[{
      let tmp = from;
      from = from.saturating_sub(1);
      tmp
    }];
    if ch == b' ' {
      chars[{
        let tmp = to;
        to -= 1;
        tmp
      }] = b'0';
      chars[{
        let tmp = to;
        to -= 1;
        tmp
      }] = b'2';
      ch = b'%';
    }
    chars[{
      let tmp = to;
      to = to.saturating_sub(1);
      tmp
    }] = ch;
  }
  ret.to_string()
}

#[gtest]
fn encode_spaces_assertions() {
  expect_that!(encode_spaces("Mr John Smith"), eq("Mr%20John%20Smith"));
  expect_that!(
    encode_spaces("a b c d e f g h i j k l m n o p q r s t u v x w z"),
    eq(
      "a%20b%20c%20d%20e%20f%20g%20h%20i%20j%20k%20l%20m%20n%20o%20p%20q%20r%20s%20t%20u%20v%20x%20w%20z"
    )
  );
  expect_that!(encode_spaces("a     "), eq("a%20%20%20%20%20"));
  expect_that!(encode_spaces("     "), eq("%20%20%20%20%20"));
  expect_that!(encode_spaces("     b"), eq("%20%20%20%20%20b"));
  expect_that!(encode_spaces("a     b"), eq("a%20%20%20%20%20b"));
}
