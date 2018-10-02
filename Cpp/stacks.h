#pragma once
#include "common.h"

class MinStack {
public:
	/** initialize your data structure here. */
	MinStack() {}

	void push(int x) {
		s1.push(x);
		if (s2.empty() || x <= s2.top()) s2.push(x);
	}

	void pop() {
		if (s1.top() == s2.top()) s2.pop();
		s1.pop();
	}

	int top() {
		return s1.top();
	}

	int getMin() {
		return s2.top();
	}

private:
	stack<int> s1, s2;
};

namespace Stacks {
	// 224. Basic Calculator
	/*
		"1 + 1" = 2
		" 2-1 + 2 " = 3
		"(1+(4+5+2)-3)+(6+8)" = 23
	 */
	int calculate(string s) {
		int res = 0;
		vector<int> sign(2, 1);
		for (int i = 0; i < s.size(); ++i) {
			char c = s[i];
			if (c >= '0') {
				int num = 0;
				while (i < s.size() && s[i] >= '0') {
					num = 10 * num + s[i++] - '0';
				}
				res += sign.back() * num;
				sign.pop_back();
				--i;
			}
			else if (c == ')') sign.pop_back();
			else if (c != ' ') sign.emplace_back(sign.back() * (c == '-' ? -1 : 1));
		}
		return res;
	}

	/**
	* 402. Remove K Digits
	Input: num = "1432219", k = 3
	Output: "1219"
	Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
	*/
	string removeKdigits(string num, int k) {
		string res = "";
		const auto n = num.size();
		auto keep = n - k;
		for (char c : num) {
			while (k && res.size() && res.back() > c) {
				res.pop_back();
				--k;
			}
			res.push_back(c);
		}
		res.resize(keep);
		while (!res.empty() && res[0] == '0') res.erase(res.begin());
		return res.empty() ? "0" : res;
	}

	// 84. Largest Rectangle in Histogram
	// Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.
	int largestRectangleArea(vector<int>& heights) {
		int n = (int)heights.size();
		if (n == 0) return 0;
		stack<int> s;
		heights.emplace_back(0);
		++n;
		int ans = 0;
		for (int i = 0; i < n; ) {
			if (s.empty() || heights[i] > heights[s.top()]) {
				s.push(i++);
			}
			else {
				int tmp = s.top();
				s.pop();
				ans = max(ans, heights[tmp] * (s.empty() ? i : i - s.top() - 1));
			}
		}
		return ans;
	}

	// 20. Valid Parentheses
	// Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
	bool isValid(string s)
	{
		string stack = "";
		for (auto c : s) {
			if (c == '(') stack += ')';
			else if (c == '[') stack += ']';
			else if (c == '{') stack += '}';
			else {
				if (stack.empty() || c != stack.back()) {
					return false;
				}
				else {
					stack.pop_back();
				}
			}

		}
		return stack.empty();
	}

	// 32. Longest Valid Parentheses
	int longestValidParentheses(string s) {
		int n = (int)s.size();
		int* f = new int[n];
		memset(f, 0, n * sizeof(int));
		int ans = 0;
		for (int i = 1; i < n; ++i) if (s[i] == ')') {
			int prev = i - f[i - 1] - 1;
			if (prev >= 0 && s[prev] == '(') {
				if (prev >= 1)
					f[i] = max(f[i], f[i - 1] + 2 + f[prev - 1]);
				else
					f[i] = max(f[i], f[i - 1] + 2);
			}
			if (s[i - 1] == '(') {
				f[i] = max(f[i], f[i - 2] + 2);
			}
			ans = max(ans, f[i]);
		}
		delete[] f;
		return ans;
	}

	// 150. Evaluate Reverse Polish Notation [M]
	// Evaluate the value of an arithmetic expression in Reverse Polish Notation. Valid operators are + , -, *, / .Each operand may be an integer or another expression.
	int evalRPN(vector<string>& tokens) {
		// reverse Polish Notation
		const int ERROR_CODE = INT_MIN;
		stack<int> stk;
		for (string s : tokens) {
			if (!s.compare("+")) {
				if (stk.size() < 2) return ERROR_CODE;
				int a = stk.top(); stk.pop();
				int b = stk.top(); stk.pop();
				stk.push(b + a);
			}
			else if (!s.compare("-")) {
				if (stk.size() < 2) return ERROR_CODE;
				int a = stk.top(); stk.pop();
				int b = stk.top(); stk.pop();
				stk.push(b - a);
			}
			else if (!s.compare("*")) {
				if (stk.size() < 2) return ERROR_CODE;
				int a = stk.top(); stk.pop();
				int b = stk.top(); stk.pop();
				stk.push(b * a);
			}
			else if (!s.compare("/")) {
				if (stk.size() < 2) return ERROR_CODE;
				int a = stk.top(); stk.pop();
				int b = stk.top(); stk.pop();
				stk.push(b / a);
			}
			else {
				stk.push(stoi(s));
			}
		}

		return (int)round(stk.top());
	}

}