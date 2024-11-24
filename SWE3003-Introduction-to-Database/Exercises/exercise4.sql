 with tmp_tab as (
	select * 
	from takes natural join course natural join department
	where year=2009 and building='Painter')
select name
from student join tmp_tab on tmp_tab.id = student.id
;
