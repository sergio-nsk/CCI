""" Implement an algorithm to determine if a string has all unique characters.
What if you cannot use additional data structures?"""

def isUnique(string):
    """ 8bit ASCII

    :param string: examing string
    """
    testChars = 0
    for ch in string:
        code = ord(ch)
        bit = 1 << code
        if (testChars & bit) != 0:
            return False
        testChars = testChars | bit
    return True

def test(string):
    """ calls isUnique with examing string and outputs its result

    :param string: examing string
    """
    print '"{}" {}'.format(string, "passed" if isUnique(string) else "not passed")

if __name__ == "__main__":
    test("IsUnique")
    test("IsUniqueTest")
