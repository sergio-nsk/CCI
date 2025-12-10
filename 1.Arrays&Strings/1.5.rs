// One Away: There are three types of edits that can be performed on strings:
// insert a character, remove a character, or replace a character. Given two
// strings, write a function to check if they are one edit (or zero edits) away.
// EXAMPLE
//  pale, ple -> true
//  pales, pale -> true
//  pale, bale -> true
//  pale, bake -> false

use googletest::prelude::*;

fn is_one_way(left: &str, right: &str) -> bool {
  let left_len: usize = left.len();
  let right_len: usize = right.len();
  if left_len.abs_diff(right_len) > 2 {
    return false;
  }

  let mut modified_count: i32 = 0;
  let mut l = left.chars();
  let mut r = right.chars();
  let mut lc = l.next();
  let mut rc = r.next();
  while lc.is_some() && rc.is_some() {
    if lc.unwrap() != rc.unwrap() {
      if modified_count > 0 {
        return false;
      }
      modified_count += 1;
      if left_len > right_len {
        lc = l.next();
        continue;
      }
      if left_len < right_len {
        rc = r.next();
        continue;
      }
    }
    lc = l.next();
    rc = r.next();
  }
  modified_count < 2
}

#[gtest]
fn is_one_way_assertions() {
  expect_true!(is_one_way("pale", "ple"));
  expect_true!(is_one_way("pales", "pale"));
  expect_true!(is_one_way("pale", "bale"));
  expect_false!(is_one_way("pale", "bake"));
  expect_false!(is_one_way("palepale", "bale"));
}
