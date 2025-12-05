// Palindrome Permutation: Given a string, write a function to check if it is a
// permutation of a palindrome. A palindrome is a word or phrase that is the
// same forwards and backwards. A permutation is a rearrangement of letters. The
// palindrome does not need to be limited to just dictionary words.
//
// EXAMPLE Input:
//  Tact Coa
// Output:
//  True (permutations: "taco cat'; "atc o eta·; etc.)

use bit_vec::BitVec;
use googletest::prelude::*;

fn is_palindrome_permutation(str: &str) -> bool {
  let mut char_count: [i32; 26] = [0; 26];
  for mut c in str.chars() {
    if c.is_alphabetic() {
      c = c.to_ascii_lowercase();
      char_count[c as usize - 'a' as usize] += 1
    }
  }
  char_count.iter().filter(|cnt| *cnt % 2 != 0).count() <= 1
}

fn is_palindrome_permutation_bitset(str: &str) -> bool {
  let mut odd_chars = BitVec::from_elem(26, false);
  for c in str.chars() {
    if c.is_alphabetic() {
      let bit = c.to_ascii_lowercase() as usize - 'a' as usize;
      odd_chars.set(bit, !odd_chars[bit]);
    }
  }
  odd_chars.count_ones() <= 1
}

#[gtest]
fn is_palindrome_permutation_assertions() {
  expect_true!(is_palindrome_permutation("Tact Coa"));
  expect_false!(is_palindrome_permutation("Tact Coat"));
  expect_true!(is_palindrome_permutation("Tacto Coa"));
  expect_true!(is_palindrome_permutation("Ota.c,t:o Co a"));
  expect_true!(is_palindrome_permutation("\"taco cat'"));
  expect_true!(is_palindrome_permutation("\"atc o atc·"));
}

#[gtest]
fn is_palindrome_permutation_bitset_assertions() {
  expect_true!(is_palindrome_permutation_bitset("Tact Coa"));
  expect_false!(is_palindrome_permutation_bitset("Tact Coat"));
  expect_true!(is_palindrome_permutation_bitset("Tacto Coa"));
  expect_true!(is_palindrome_permutation_bitset("Ota.c,t:o Co a"));
  expect_true!(is_palindrome_permutation_bitset("\"taco cat'"));
  expect_true!(is_palindrome_permutation_bitset("\"atc o atc·"));
}
