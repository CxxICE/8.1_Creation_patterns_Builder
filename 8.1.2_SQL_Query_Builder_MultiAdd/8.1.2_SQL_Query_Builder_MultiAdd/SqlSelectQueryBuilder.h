#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>

class SqlSelectQueryBuilder
{
public:
	SqlSelectQueryBuilder() = default;
	SqlSelectQueryBuilder &AddColumn(const std::string &column);
	SqlSelectQueryBuilder &AddFrom(const std::string &table);
	SqlSelectQueryBuilder &AddWhere(const std::string &field, const std::string &value);
	SqlSelectQueryBuilder &AddWhere(const std::multimap<std::string, std::string> &kv) noexcept;
	SqlSelectQueryBuilder &AddColumns(const std::vector<std::string> &columns) noexcept;
	std::string BuildQuery();

private:
	std::string _table;
	std::set<std::string> _columns;
	std::multimap<std::string, std::string> _conditions;
};

