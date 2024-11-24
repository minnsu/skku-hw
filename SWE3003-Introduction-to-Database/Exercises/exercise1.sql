with build_count(building, b_c)
	as (select building, count(building)
		from course natural join department
		group by building)
select building
from build_count
where build_count.b_c >= all (select b_c 
				from build_count);
