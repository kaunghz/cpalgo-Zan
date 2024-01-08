#include <bits/stdc++.h>

class stringhash {
    private:
    std::string _mystr;
    long long hashval;

    void _computeLPSArray(std::string pattern, int M, int* lps) {
        int len = 0, i = 1;
        lps[0] = 0;
        while (i < M) {
            if (pattern[i] == pattern[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) len = lps[len - 1];
                else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }

    inline std::string _substr(const int& start, const int& end) {
        return _mystr.substr(start, end-start+1);
    }

    public:
    explicit stringhash(const std::string& s) : _mystr(s) {}

    stringhash operator+(const stringhash& oth) const { return stringhash(_mystr + oth._mystr); }
    bool operator==(const stringhash& oth) const { return (_mystr == oth._mystr); }

    inline std::string getStr() const {
        return _mystr;
    }

    inline uint32_t len() const {
        return _mystr.length();
    }

    long long hash(const int& start, const int& end) {
        const std::string s = _substr(start, end);
        const int p = 31;
        const int m = 1e9 + 9;
        long long hash_value = 0;
        long long p_pow = 1;
        for (char c : s) {
            hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }
        return hash_value;
    }

    bool isPalindrome(const int& start, const int& end) {
        const std::string s = _substr(start, end);
        uint32_t l = 0, r = s.length()-1;
        bool res = 1;
        while (res && l<r) res = (s[l++] == s[r--]);
        return res;
    }

    /*
    KMPSearch returns all the beginning indices of the matched pattern O(N+M)
    "ababa" pattern "aba" -> [0,2]
    */
    std::vector<int> KMPSearch(std::string pattern) {
        std::vector<int> res;
        int M = pattern.length(), N = len(), lps[M], i = 0, j = 0;
        _computeLPSArray(pattern, M, lps);
        while ((N - i) >= (M - j)) {
            if (pattern[j] == _mystr[i]) {
                j++; i++;
            }
            if (j == M) {
                res.push_back(i-j);
                j = lps[j - 1];
            } else if (i < N && pattern[j] != _mystr[i])
                (j != 0) ? j = lps[j - 1] : i = i + 1;
        }
        return res;
    }

    std::vector<std::string> splitter(const std::string& del) {
        std::vector<std::string> res;
        int start, end = -1*del.size();
        do {
            start = end + del.size();
            end = _mystr.find(del, start);
            res.push_back(_mystr.substr(start, end - start));
        } while (end != -1);
        return res;
    }

    // LCSubStr returns the longest common substring in O(mn)
    std::string LCSubStr(const std::string othstr) {
        int m = len(), n = othstr.length();
        int LCSuff[m + 1][n + 1], len = 0, row, col;
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                if (i == 0 || j == 0) LCSuff[i][j] = 0;
                else if (_mystr[i - 1] == othstr[j - 1]) {
                    LCSuff[i][j] = LCSuff[i - 1][j - 1] + 1;
                    if (len < LCSuff[i][j]) {
                        len = LCSuff[i][j];
                        row = i;
                        col = j;
                    }
                }
                else LCSuff[i][j] = 0;
            }
        }
        if (len == 0) return "";
        char* res = (char*)malloc((len + 1) * sizeof(char));
        while (LCSuff[row][col] != 0) {
            res[--len] = _mystr[row - 1];
            row--;
            col--;
        }
        return res;
    }

};

int main() {
    return 0;
}
