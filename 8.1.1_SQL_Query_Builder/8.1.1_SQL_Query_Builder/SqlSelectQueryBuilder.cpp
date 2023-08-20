#include "SqlSelectQueryBuilder.h"

SqlSelectQueryBuilder &SqlSelectQueryBuilder::AddColumn(const std::string &column)
{
	_columns.insert(column);
	return *this;
}

SqlSelectQueryBuilder &SqlSelectQueryBuilder::AddFrom(const std::string &table)
{
	_table = table;
	return *this;
}

SqlSelectQueryBuilder &SqlSelectQueryBuilder::AddWhere(const std::string &field, const std::string &value)
{
	_conditions.insert(std::pair(field, value));
	return *this;
}

std::string SqlSelectQueryBuilder::BuildQuery()
{
	std::string query = "SELECT";
	if (_columns.empty())
	{
		query += " *";
	}
	else
	{
		int count_columns = 0;
		int columns_size = _columns.size();
		for (const auto &column : _columns)
		{
			++count_columns;
			query = query + " " + column;
			if (count_columns < columns_size)
			{
				query += ",";
			}
		}
	}

	query += " FROM " + _table;

	if (!_conditions.empty())
	{
		query += " WHERE";
		int count_conditions = 0;
		int conditions_size = _conditions.size();
		for (auto it = _conditions.begin(); it != _conditions.end(); ++it)
		{	
			++count_conditions;
			if (count_conditions > 1)
			{
				query += " AND";
			}
			int amount_one_condition = _conditions.count((*it).first);
			if (amount_one_condition == 1)
			{
				query = query + " " + (*it).first + " = " + (*it).second;
			}
			else
			{
				int count_for_in = 1;
				query = query + " " + (*it).first + " IN(" + (*it).second;
				do
				{
					++it;
					++count_for_in;
					query = query + ", " + (*it).second;
				} while (count_for_in < amount_one_condition);
				query += ")";
			}
			
		}		
	}
	query += ";";
	return query;
}