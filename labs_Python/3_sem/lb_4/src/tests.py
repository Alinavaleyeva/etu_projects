from algoritm import algoritm_rabin_karp

def test_moevm():
    pat = "aba"
    txt = "abacaba"
    q = 101
    my_answer = algoritm_rabin_karp(pat, txt, q)
    answer = [0, 4]
    assert my_answer == answer

def test_empty():
    pat = "aba"
    txt = "abccabd"
    q = 101
    my_answer = algoritm_rabin_karp(pat, txt, q)
    answer = []
    assert my_answer == answer

def test_equal():
    pat = "aba"
    txt = "aba"
    q = 101
    my_answer = algoritm_rabin_karp(pat, txt, q)
    answer = [0]
    assert my_answer == answer

def test_large_values():
    pat = "cbhadgfvcagvc"
    txt = "cbhadgfvcagvcvbshcbdchvbhdsbjkcvhbwdsjkcbcbhadgfvcagvcwdjscvhbdcbhadgfvcagvcsjbvsnc"
    q = 101
    my_answer = algoritm_rabin_karp(pat, txt, q)
    answer = [0, 41, 63]
    assert my_answer == answer

def test_incorrect_len():
    pat = "cbhadgfvcagvc"
    txt = "a"
    q = 101
    my_answer = algoritm_rabin_karp(pat, txt, q)
    answer = []
    assert my_answer == answer