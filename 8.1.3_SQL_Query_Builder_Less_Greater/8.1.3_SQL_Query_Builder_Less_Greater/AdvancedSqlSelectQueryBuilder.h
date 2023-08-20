#pragma once
#include "SqlSelectQueryBuilder.h"
class AdvancedSqlSelectQueryBuilder : public SqlSelectQueryBuilder
{
public:
	AdvancedSqlSelectQueryBuilder &addWhereLessOr(const std::string &field, const std::string &value);
	AdvancedSqlSelectQueryBuilder &addWhereLessAnd(const std::string &field, const std::string &value);
	AdvancedSqlSelectQueryBuilder &addWhereMoreOr(const std::string &field, const std::string &value);
	AdvancedSqlSelectQueryBuilder &addWhereMoreAnd(const std::string &field, const std::string &value);
	
	std::string BuildQuery() override;
private:
	std::map<std::string, std::string> _conditions_less_or;
	std::map<std::string, std::string> _conditions_less_and;
	std::map<std::string, std::string> _conditions_more_or;
	std::map<std::string, std::string> _conditions_more_and;
};

