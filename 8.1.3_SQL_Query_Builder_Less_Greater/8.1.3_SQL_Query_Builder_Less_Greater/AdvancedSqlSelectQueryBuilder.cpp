#include "AdvancedSqlSelectQueryBuilder.h"

AdvancedSqlSelectQueryBuilder &AdvancedSqlSelectQueryBuilder::addWhereMoreOr(const std::string &field, const std::string &value)
{
	_conditions_more_or.insert(std::pair(field, value));
	return *this;
}

AdvancedSqlSelectQueryBuilder &AdvancedSqlSelectQueryBuilder::addWhereMoreAnd(const std::string &field, const std::string &value)
{
	_conditions_more_and.insert(std::pair(field, value));
	return *this;
}

AdvancedSqlSelectQueryBuilder &AdvancedSqlSelectQueryBuilder::addWhereLessOr(const std::string &field, const std::string &value)
{
	_conditions_less_or.insert(std::pair(field, value));
	return *this;
}

AdvancedSqlSelectQueryBuilder &AdvancedSqlSelectQueryBuilder::addWhereLessAnd(const std::string &field, const std::string &value)
{
	_conditions_less_and.insert(std::pair(field, value));
	return *this;
}

std::string AdvancedSqlSelectQueryBuilder::BuildQuery()
{
	std::string query = SqlSelectQueryBuilder::BuildQuery();
	query.pop_back();//удаление точки с запятой

	//проверка наличия WHERE
	size_t where_pos = query.find("WHERE");
	bool need_pretext = true;
	if (where_pos == std::string::npos && (!_conditions_less_or.empty() || !_conditions_less_and.empty() || !_conditions_more_or.empty() || !_conditions_more_and.empty()))
	{
		query += " WHERE";
		need_pretext = false;
	}

	if (!_conditions_more_or.empty())
	{		
		int count_conditions = 0;
		int conditions_size = _conditions_more_or.size();
		for (auto it = _conditions_more_or.begin(); it != _conditions_more_or.end(); ++it)
		{
			++count_conditions;
			if (count_conditions > 1 || need_pretext)
			{
				query += " OR";
			}
			query = query + " " + (*it).first + " > " + (*it).second;
		}
		need_pretext = true;
	}

	if (!_conditions_less_and.empty())
	{

		int count_conditions = 0;
		int conditions_size = _conditions_less_and.size();
		for (auto it = _conditions_less_and.begin(); it != _conditions_less_and.end(); ++it)
		{
			++count_conditions;
			if (count_conditions > 1 || need_pretext)
			{
				query += " AND";
			}
			query = query + " " + (*it).first + " < " + (*it).second;
		}
		need_pretext = true;
	}

	if (!_conditions_less_or.empty())
	{

		int count_conditions = 0;
		int conditions_size = _conditions_less_or.size();
		for (auto it = _conditions_less_or.begin(); it != _conditions_less_or.end(); ++it)
		{
			++count_conditions;
			if (count_conditions > 1 || need_pretext)
			{
				query += " OR";
			}
			query = query + " " + (*it).first + " < " + (*it).second;
		}
		need_pretext = true;
	}

	if (!_conditions_more_and.empty())
	{
		int count_conditions = 0;
		int conditions_size = _conditions_more_and.size();
		for (auto it = _conditions_more_and.begin(); it != _conditions_more_and.end(); ++it)
		{
			++count_conditions;
			if (count_conditions > 1 || need_pretext)
			{
				query += " AND";
			}
			query = query + " " + (*it).first + " > " + (*it).second;
		}
		need_pretext = true;
	}

	

	
	query += ";";
	return query;
}


