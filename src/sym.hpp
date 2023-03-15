#ifndef BCTL_SYM_HPP
#define BCTL_SYM_HPP

#include <string>

namespace bctl {

enum class type : int {
	var, uin,
	sin, flo,
	una, bin,
	par
};

enum class paren : int {
	lpa, rpa
};

enum class unary : int {
	neg, abs,
	fac, sin,
	cos, tan,
	csc, sec,
	cot, nlo,
	der, ing
};

enum class binary : int {
	add, sub,
__1,
	mul, div, mod,
__2,
	exp, log,
__3
};

class sym {
	union {
		std::string        *var;
		unsigned long long  uin;
		long long           sin;
		double              flo;
		unary               una;
		binary              bin;
		paren               par;
	}    m_data;

	type m_type;

	// char _pad[4];

	int precedence(void) const;

	friend bool operator==(const sym &l, const sym &r);

	friend bool operator>(const sym &l, const sym &r);

public:

	sym(const sym &s);

	sym(sym &&s) noexcept;

	sym &operator=(const sym &s);

	sym &operator=(sym &&s) noexcept;

	explicit sym(const char *v);

	explicit sym(const std::string &v);

	explicit sym(const unsigned long long &v);

	explicit sym(const long long &v);

	explicit sym(const double &v);

	explicit sym(const unary &v);

	explicit sym(const binary &v);

	explicit sym(const paren &v);

	~sym();

	type get_type(void) const;
};

bool operator==(const sym &l, const sym &r);

bool operator!=(const sym &l, const sym &r);

bool operator>(const sym &l, const sym &r);

bool operator<(const sym &l, const sym &r);

bool operator>=(const sym &l, const sym &r);

bool operator<=(const sym &l, const sym &r);

}

#endif
