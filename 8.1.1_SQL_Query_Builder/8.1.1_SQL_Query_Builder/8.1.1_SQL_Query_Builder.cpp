#include <iostream>
#include <cassert>

#include "SqlSelectQueryBuilder.h"

int main()
{
	{
		SqlSelectQueryBuilder query_builder;
		query_builder.AddColumn("name").AddColumn("phone");
		query_builder.AddFrom("students");
		query_builder.AddWhere("id", "42").AddWhere("name", "John");

		std::string result = query_builder.BuildQuery();
		
		assert(result == "SELECT name, phone FROM students WHERE id = 42 AND name = John;");
	}

	{
		SqlSelectQueryBuilder query_builder;
		query_builder.AddFrom("students");
		query_builder.AddWhere("id", "42").AddWhere("name", "John");

		std::string result = query_builder.BuildQuery();

		assert(result == "SELECT * FROM students WHERE id = 42 AND name = John;");
	}

	{
		SqlSelectQueryBuilder query_builder;
		query_builder.AddColumn("name").AddColumn("phone");
		query_builder.AddFrom("students");
		query_builder.AddWhere("id", "42").AddWhere("name", "John");
		query_builder.AddWhere("id", "43").AddWhere("name", "Kate");

		std::string result = query_builder.BuildQuery();

		assert(result == "SELECT name, phone FROM students WHERE id IN(42, 43) AND name IN(John, Kate);");
	}

	return 0;
}

