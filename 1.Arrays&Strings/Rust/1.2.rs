// Check Permutation: Given two strings, write a method to decide if one is a
// permutation of the other.

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

fn main() {
  assert!(check_permutation("TestPermutation", "PermutationTest"));
  assert!(check_permutation("TestPermutation", "PeermutatTstion"));
  assert!(!check_permutation("TestPermutation", "RotationTest"));
  assert!(!check_permutation("TestPermutation", "Permutationtest"));
}
