#include "sym.hpp"

bctl::sym::sym(const sym &s) : m_type(s.m_type)
{
	switch (m_type) {
	case type::var:
		m_data.var = new std::string(*s.m_data.var);
		break;
	case type::uin:
		m_data.uin = s.m_data.uin;
		break;
	case type::sin:
		m_data.sin = s.m_data.sin;
		break;
	case type::flo:
		m_data.flo = s.m_data.flo;
		break;
	case type::una:
		m_data.una = s.m_data.una;
		break;
	case type::bin:
		m_data.bin = s.m_data.bin;
		break;
	case type::par:
		m_data.par = s.m_data.par;
		break;
	}
}

bctl::sym::sym(sym &&s) noexcept : m_type(s.m_type)
{
	switch (m_type) {
	case type::var:
		m_data.var = s.m_data.var;
		s.m_data.var = nullptr;
		break;
	case type::uin:
		m_data.uin = s.m_data.uin;
		break;
	case type::sin:
		m_data.sin = s.m_data.sin;
		break;
	case type::flo:
		m_data.flo = s.m_data.flo;
		break;
	case type::una:
		m_data.una = s.m_data.una;
		break;
	case type::bin:
		m_data.bin = s.m_data.bin;
		break;
	case type::par:
		m_data.par = s.m_data.par;
		break;
	}
}

bctl::sym &bctl::sym::operator=(const sym &s)
{
	if (this != &s) {
		this->~sym();
		new (this) sym(s);
	}

	return *this;
}

bctl::sym &bctl::sym::operator=(sym &&s) noexcept
{
	if (this != &s) {
		this->~sym();
		new (this) sym(std::move(s));
	}

	return *this;
}

bctl::sym::sym(const char *v)
{
	m_data.var = new std::string(v);
	m_type = type::var;
}

bctl::sym::sym(const std::string &v)
{
	m_data.var = new std::string(v);
	m_type = type::var;
}

bctl::sym::sym(const unsigned long long &v)
{
	m_data.uin = v;
	m_type = type::uin;
}

bctl::sym::sym(const long long &v)
{
	m_data.sin = v;
	m_type = type::sin;
}

bctl::sym::sym(const double &v)
{
	m_data.flo = v;
	m_type = type::flo;
}

bctl::sym::sym(const unary &v)
{
	m_data.una = v;
	m_type = type::una;
}

bctl::sym::sym(const binary &v)
{
	m_data.bin = v;
	m_type = type::bin;
}

bctl::sym::sym(const paren &v)
{
	m_data.par = v;
	m_type = type::par;
}

bctl::sym::~sym()
{
	if (m_type == type::var)
		delete m_data.var;
}

bctl::type bctl::sym::get_type(void) const
{
	return m_type;
}

int bctl::sym::precedence(void) const
{
	if (m_data.bin < binary::__1)
		return 1;
	if (m_data.bin < binary::__2)
		return 2;
	return 3;
}

bool bctl::operator==(const sym &l, const sym &r)
{
	switch (l.m_type) {
	case type::uin:
		switch (r.m_type) {
		case type::uin:
			return l.m_data.uin == r.m_data.uin;
		case type::sin:
			return static_cast<long long>(l.m_data.uin) == r.m_data.sin;
		case type::flo:
			return static_cast<double>(l.m_data.uin) == r.m_data.flo;
		default:
			return false;
		}
	case type::sin:
		switch (r.m_type) {
		case type::uin:
			return l.m_data.sin == static_cast<long long>(r.m_data.uin);
		case type::sin:
			return l.m_data.sin == r.m_data.sin;
		case type::flo:
			return static_cast<double>(l.m_data.sin) == r.m_data.flo;
		default:
			return false;
		}
	case type::flo:
		switch (r.m_type) {
		case type::uin:
			return l.m_data.flo == static_cast<double>(r.m_data.uin);
		case type::sin:
			return l.m_data.flo == static_cast<double>(r.m_data.sin);
		case type::flo:
			return l.m_data.flo == r.m_data.flo;
		default:
			return false;
		}
	case type::una:
		switch (r.m_type) {
		case type::una:
			return true;
		default:
			return false;
		}
	case type::bin:
		switch (r.m_type) {
		case type::bin:
			return l.precedence() == r.precedence();
		default:
			return false;
		}
	default:
		return false;
	}
}

bool bctl::operator!=(const sym &l, const sym &r)
{
	return !(l == r);
}

bool bctl::operator>(const sym &l, const sym &r)
{
	switch (l.m_type) {
	case type::uin:
		switch (r.m_type) {
		case type::uin:
			return l.m_data.uin > r.m_data.uin;
		case type::sin:
			return static_cast<long long>(l.m_data.uin) > r.m_data.sin;
		case type::flo:
			return static_cast<double>(l.m_data.uin) > r.m_data.flo;
		default:
			return false;
		}
	case type::sin:
		switch (r.m_type) {
		case type::uin:
			return l.m_data.sin > static_cast<long long>(r.m_data.uin);
		case type::sin:
			return l.m_data.sin > r.m_data.sin;
		case type::flo:
			return static_cast<double>(l.m_data.sin) > r.m_data.flo;
		default:
			return false;
		}
	case type::flo:
		switch (r.m_type) {
		case type::uin:
			return l.m_data.flo > static_cast<double>(r.m_data.uin);
		case type::sin:
			return l.m_data.flo > static_cast<double>(r.m_data.sin);
		case type::flo:
			return l.m_data.flo > r.m_data.flo;
		default:
			return false;
		}
	case type::una:
		switch (r.m_type) {
		case type::bin:
			return true;
		default:
			return false;
		}
	case type::bin:
		switch (r.m_type) {
		case type::bin:
			return l.precedence() > r.precedence();
		default:
			return false;
		}
	default:
		return false;
	}
}

bool bctl::operator<(const sym &l, const sym &r)
{
	return !(l == r || l > r);
}

bool bctl::operator>=(const sym &l, const sym &r)
{
	return l == r || l > r;
}

bool bctl::operator<=(const sym &l, const sym &r)
{
	return l == r || l < r;
}
