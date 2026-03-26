#ifndef LINECIPHER_H
#define LINECIPHER_H

#include <string>
#include <vector>
#include <utility>

namespace linecipher {

inline const std::string& charset() {
    static const std::string chs = " etaoinsrhlcdumfpwgbyvkxjqz1234567890,./>@()!";
    return chs;
}

inline std::vector<std::string>& topVec() { static std::vector<std::string> v(100); return v; }
inline std::vector<std::string>& midVec() { static std::vector<std::string> v(100); return v; }
inline std::vector<std::string>& botVec() { static std::vector<std::string> v(100); return v; }
inline std::vector<int>& ciphons() { static std::vector<int> v; return v; }
inline bool& inited() { static bool f = false; return f; }

inline void dfs(int cur, int pre, int x, int max_x, int& tp) {
    if (x == max_x) {
        int div = 1;
        for (int i = 1; i < x; ++i) div *= 10;
        int fst = x > 0 ? (cur / (div == 0 ? 1 : div)) : 0;
        int lst = x > 0 ? (cur % 10) : 0;
        if ((fst == 2 || fst == 4 || fst == 5 || fst == 7) || (lst == 1 || lst == 4 || lst == 6 || lst == 7)) return;
        ciphons().push_back(cur);
        tp++;
        return;
    }

    static const std::pair<int, int> valid_pairs[] = {
        {1, 2}, {1, 4}, {2, 1}, {2, 3}, {2, 6}, {3, 1}, {3, 3}, {3, 6},
        {4, 2}, {4, 4}, {5, 1}, {5, 3}, {5, 6}, {6, 5}, {6, 7}, {7, 5}, {7, 7}
    };

    for (int i = 1; i <= 7; ++i) {
        if ((pre >> i) & 1) continue;
        if (x > 0) {
            int last_digit = cur % 10;
            bool is_valid = false;
            for (auto& p : valid_pairs) {
                if (p.first == last_digit && p.second == i) { is_valid = true; break; }
            }
            if (!is_valid) continue;
        }
        dfs(cur * 10 + i, pre | (1 << i), x + 1, max_x, tp);
    }
}

inline void drawLine(int num, int x) {
    auto& top = topVec();
    auto& mid = midVec();
    auto& bot = botVec();
    top[x].clear();
    mid[x].clear();
    bot[x].clear();
    std::string txt = std::to_string(num);
    for (char c : txt) {
        switch (c) {
            case '1': top[x] += ' '; mid[x] += '/'; bot[x] += ' '; break;
            case '2': top[x] += ' '; mid[x] += '\\'; bot[x] += ' '; break;
            case '3': top[x] += ' '; mid[x] += '_'; bot[x] += ' '; break;
            case '4': top[x] += '_'; mid[x] += ' '; bot[x] += ' '; break;
            case '5': top[x] += ' '; mid[x] += ' '; bot[x] += '/'; break;
            case '6': top[x] += ' '; mid[x] += ' '; bot[x] += '\\'; break;
            case '7': top[x] += ' '; mid[x] += ' '; bot[x] += '_'; break;
        }
    }
    top[x] += ' ';
    mid[x] += ' ';
    bot[x] += '|';
}

inline char defineLine(const std::string& xtop, const std::string& xmid, const std::string& xbot) {
    const auto& top = topVec();
    const auto& mid = midVec();
    const auto& bot = botVec();
    const std::string& chs = charset();
    for (int i = 0; i < 100 && i < static_cast<int>(chs.size()); ++i) {
        if (top[i] == xtop && mid[i] == xmid && bot[i] == xbot) {
            return chs[i];
        }
    }
    return '?';
}

inline void generate() {
    int cnt = 0;
    for (int max_x = 1; max_x <= 7; ++max_x) {
        int tp = 0;
        ciphons().clear();
        dfs(0, 0, 0, max_x, tp);
        for (int i = 0; i < tp; ++i) {
            drawLine(ciphons()[i], cnt++);
        }
    }
}

inline void init(bool /*debug*/ = false) {
    if (!inited()) {
        generate();
        inited() = true;
    }
}

inline std::string encode(const std::string& input) {
    init();
    const auto& chs = charset();
    const auto& top = topVec();
    const auto& mid = midVec();
    const auto& bot = botVec();
    std::string result_top, result_mid, result_bot;
    std::vector<int> index(input.size(), -1);
    for (size_t i = 0; i < input.size(); ++i) {
        index[i] = static_cast<int>(chs.find(input[i]));
    }
    for (size_t i = 0; i < input.size(); ++i) result_top += top[index[i]];
    for (size_t i = 0; i < input.size(); ++i) result_mid += mid[index[i]];
    for (size_t i = 0; i < input.size(); ++i) result_bot += bot[index[i]];
    return result_top + "|\n" + result_mid + "|\n" + result_bot + "\n";
}

inline std::string decode(std::string itop, std::string imid, std::string ibot) {
    init();
    if (!itop.empty() && (itop.back() == '|' || itop.back() == '\r')) {
        if (itop.back() == '\r') itop.pop_back();
        if (!itop.empty() && itop.back() == '|') itop.back() = ' ';
    }
    if (!imid.empty() && (imid.back() == '|' || imid.back() == '\r')) {
        if (imid.back() == '\r') imid.pop_back();
        if (!imid.empty() && imid.back() == '|') imid.back() = ' ';
    }
    if (!ibot.empty() && ibot.back() == '\r') ibot.pop_back();
    std::string result;
    std::vector<int> sep;
    sep.push_back(-1);
    for (size_t i = 0; i < ibot.length(); ++i) {
        if (ibot[i] == '|') sep.push_back(static_cast<int>(i));
    }
    for (size_t i = 0; i + 1 < sep.size(); ++i) {
        int l = sep[i] + 1;
        int r = sep[i + 1];
        result += defineLine(itop.substr(l, r - l), imid.substr(l, r - l), ibot.substr(l, r - l));
    }
    return result;
}

}  // namespace linecipher

#endif

