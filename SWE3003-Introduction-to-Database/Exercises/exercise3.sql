with group_in(ins_id, nos) as (select i_id, count(s_id)
				from advisor
				group by i_id)
select id, name, dept_name, nos
from group_in join instructor on group_in.ins_id = instructor.id;
