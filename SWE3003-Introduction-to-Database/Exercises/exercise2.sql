with build_count(building, b_c)
	as (select building, count(building)
		from course natural join department
		group by building
	)
select building
from build_count
order by b_c desc
OFFSET 1
LIMIT 1;

