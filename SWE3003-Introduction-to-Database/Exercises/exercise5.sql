with w2009_tab(course_id) as (select course_id 
			from takes natural join student 
			where name='Williams' and year=2009),
     prereq_of_w2009(preq_id) as (select prereq_id
			from prereq natural join w2009_tab),
     id_and_title(ins_id, preq_title) as (select id, title
			from teaches join prereq_of_w2009 on preq_id=teaches.course_id join course on preq_id=course.course_id)
select name, preq_title
from instructor join id_and_title on ins_id=id;
