#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

const string chs = " etaoinsrhlcdumfpwgbyvkxjqz1234567890./>@:()!";
vector<string> top(100), mid(100), bot(100);
vector<int> vciphons;
int tp = 0;

void dfs(int cur, int pre, int x, int max_x) {
    if (x == max_x) {
        int fst = cur / pow(10, x - 1);
        int lst = cur % 10;
        if ((fst == 2 || fst == 4 || fst == 5 || fst == 7) || (lst == 1 || lst == 4 || lst == 6 || lst == 7)) return;
        vciphons.push_back(cur);
        tp++;
        return;
    }

    vector<pair<int, int>> valid_pairs = {{1, 2}, {1, 4}, {2, 1}, {2, 3}, {2, 6}, {3, 1}, {3, 3}, {3, 6}, {4, 2}, {4, 4}, {5, 1}, {5, 3}, {5, 6}, {6, 5}, {6, 7}, {7, 5}, {7, 7}};

    for (int i = 1; i <= 7; ++i) {
        if ((pre >> i) & 1) continue;
        if (x > 0) {
            int last_digit = cur % 10;
            bool is_valid = false;
            for (auto& pair : valid_pairs) {
                if (pair.first == last_digit && pair.second == i) {
                    is_valid = true;
                    break;
                }
            }
            if (!is_valid) continue;
        }

        dfs(cur * 10 + i, pre | (1 << i), x + 1, max_x);
    }
}

void drawVave(int num, int x) {
    top[x] = mid[x] = bot[x] = "";
    string txt = to_string(num);
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
    top[x] += ' '; mid[x] += ' '; bot[x] += '|';
    cout<<top[x]<<endl<<mid[x]<<endl<<bot[x]<<endl;
}

char defineWave(const string& xtop, const string& xmid, const string& xbot) {
    for (int i = 0; i < 100; ++i) {
        if (top[i] == xtop && mid[i] == xmid && bot[i] == xbot) {
            return chs[i];
        }
    }
    return '?';
}

void generate() {
    int cnt = 0;

    for (int max_x = 1; max_x <= 7; ++max_x) {
        tp = 0;
        vciphons.clear();
        dfs(0, 0, 0, max_x);
        for (int i = 0; i < tp; ++i) {
            cout<<"index: "<<cnt<<"  character: "<<chs[cnt]<<endl;
            drawVave(vciphons[i], cnt++);
        }
    }
}

string str2wave(const string& input) {
    string result_top, result_mid, result_bot;
    vector<int> index(input.size(), -1);
    for (size_t i = 0; i < input.size(); ++i) {
        index[i] = chs.find(input[i]);
    }

    for (size_t i = 0; i < input.size(); ++i) result_top += top[index[i]];
    for (size_t i = 0; i < input.size(); ++i) result_mid += mid[index[i]];
    for (size_t i = 0; i < input.size(); ++i) result_bot += bot[index[i]];

    return result_top + "\b|\n" + result_mid + "\b|\n" + result_bot + '\n';
}

string wave2str(string& itop, string& imid, string& ibot) {
    itop[itop.size() - 1] = ' ';
    imid[imid.size() - 1] = ' ';
    string result;
    vector<int> sep;
    sep.push_back(-1);

    for (size_t i = 0; i < ibot.length(); ++i) {
        if (ibot[i] == '|') sep.push_back(i);
    }

    for (size_t i = 0; i < sep.size() - 1; ++i) {
        result += defineWave(itop.substr(sep[i] + 1, sep[i + 1] - sep[i]),
                             imid.substr(sep[i] + 1, sep[i + 1] - sep[i]),
                             ibot.substr(sep[i] + 1, sep[i + 1] - sep[i]));
    }

    return result;
}

int main() {
    generate();

    while (true) {
        cout << "Choose one of the following options:\n  1. string 2 wave\n  2. wave 2 string\n  3. exit\n\nInput(1/2): ";
        int opt;
        cin >> opt;
        if (opt == 1) {
            string input;
            cout << "input a string: ";
            cin.ignore();
            getline(cin, input);
            cout << str2wave(input)<<endl<<"Press enter to choose again";
            cin.get();
        } else if (opt == 2) {
            string itop, imid, ibot;
            cout << "Input the wavecipher text: \n\n";
            cin.ignore();
            getline(cin, itop);
            getline(cin, imid);
            getline(cin, ibot);
            cout << "Output: " << wave2str(itop, imid, ibot)<<endl<<"Press enter to choose again";
            cin.get();
        } else if (opt == 3) exit(0);
        else continue;
    }

    return 0;
}

