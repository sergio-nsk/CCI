// Is Unique: Implement an algorithm to determine if a string has all unique
// characters. What if you cannot use additional data structures?

use std::collections::HashSet;

fn is_unique(chars: &str) -> bool {
  // 8bit ASCII
  let mut test_chars: [u64; 4] = [0; 4];
  for c in chars.as_bytes() {
    let i: u8 = c >> 6;
    let bit: u64 = 1 << (c & 0b00111111);
    if test_chars[i as usize] & bit != 0 {
      return false;
    }
    test_chars[i as usize] |= bit;
  }
  return true;
}

fn is_unique_u(chars: &str) -> bool {
  // UTF-8
  let mut test_chars = HashSet::new();
  for c in chars.chars() {
    if test_chars.get(&c) != None {
      return false;
    }
    test_chars.insert(c);
  }
  return true;
}

fn main() {
  assert!(is_unique("IsUnique"));
  assert!(!is_unique("IsUniqueTest"));
  // IsUniqueУникальный
  assert!(!is_unique_u(
    "IsUnique\u{0423}\u{043d}\u{0438}\u{043a}\u{0430}\u{043b}\u{044c}\u{043d}\u{044b}\u{0439}"
  ));
  // IsUniqueУникаль
  assert!(is_unique_u(
    "IsUnique\u{0423}\u{043d}\u{0438}\u{043a}\u{0430}\u{043b}\u{044c}"
  ));
  // zß水🍌
  assert!(is_unique_u("z\u{00df}\u{6c34}\u{01f34c}"));
  // zß水🍌ß
  assert!(!is_unique_u("z\u{00df}\u{6c34}\u{01f34c}\u{00df}"));
}
