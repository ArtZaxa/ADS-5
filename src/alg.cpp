// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

static bool isOp(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

static int priority(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

static void addToken(std::string& out, const std::string& token) {
    if (!out.empty()) {
        out += ' ';
    }
    out += token;
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> ops;
    std::string out;

    for (std::size_t i = 0; i < inf.size();) {
        if (std::isspace(static_cast<unsigned char>(inf[i]))) {
            ++i;
            continue;
        }

        if (std::isdigit(static_cast<unsigned char>(inf[i]))) {
            std::size_t j = i;
            while (j < inf.size() && std::isdigit(static_cast<unsigned char>(inf[j]))) {
                ++j;
            }

            addToken(out, inf.substr(i, j - i));
            i = j;
            continue;
        }

        if (inf[i] == '(') {
            ops.push(inf[i]);
            ++i;
            continue;
        }

        if (inf[i] == ')') {
            while (!ops.isEmpty() && ops.get() != '(') {
                addToken(out, std::string(1, ops.get()));
                ops.pop();
            }
            if (!ops.isEmpty() && ops.get() == '(') {
                ops.pop();
            }
            ++i;
            continue;
        }

        if (isOp(inf[i])) {
            char cur = inf[i];

            while (!ops.isEmpty() &&
                   ops.get() != '(' &&
                   priority(ops.get()) >= priority(cur)) {
                addToken(out, std::string(1, ops.get()));
                ops.pop();
            }

            ops.push(cur);
            ++i;
            continue;
        }

        ++i;
    }

    while (!ops.isEmpty()) {
        if (ops.get() != '(' && ops.get() != ')') {
            addToken(out, std::string(1, ops.get()));
        }
        ops.pop();
    }

    return out;
}

int eval(const std::string& post) {
    TStack<int, 100> values;

    for (std::size_t i = 0; i < post.size();) {
        if (std::isspace(static_cast<unsigned char>(post[i]))) {
            ++i;
            continue;
        }

        if (std::isdigit(static_cast<unsigned char>(post[i]))) {
            int value = 0;
            while (i < post.size() && std::isdigit(static_cast<unsigned char>(post[i]))) {
                value = value * 10 + (post[i] - '0');
                ++i;
            }
            values.push(value);
            continue;
        }

        if (isOp(post[i])) {
            int right = values.get();
            values.pop();

            int left = values.get();
            values.pop();

            int result = 0;

            if (post[i] == '+') {
                result = left + right;
            } else if (post[i] == '-') {
                result = left - right;
            } else if (post[i] == '*') {
                result = left * right;
            } else if (post[i] == '/') {
                result = left / right;
            }

            values.push(result);
        }

        ++i;
    }

    return values.get();
}
