// Check Permutation: Given two strings, write a method to decide if one is a
// permutation of the other.

use googletest::prelude::*;

fn check_permutation(one: &str, two: &str) -> bool {
  if one.len() != two.len() {
    return false;
  }

  let mut char_count: [i32; 256] = [0; 256];
  for c in one.as_bytes() {
    char_count[*c as usize] += 1;
  }
  for c in two.as_bytes() {
    char_count[*c as usize] -= 1;
    if char_count[*c as usize] < 0 {
      return false;
    }
  }
  return true;
}

#[gtest]
fn check_permutation_assertions() {
  expect_true!(check_permutation("TestPermutation", "PermutationTest"));
  expect_true!(check_permutation("TestPermutation", "PeermutatTstion"));
  expect_false!(check_permutation("TestPermutation", "RotationTest"));
  expect_false!(check_permutation("TestPermutation", "Permutationtest"));
}
