create table temp (
    id           int unsigned not null primary key auto_increment,
    meter_id     int unsigned not null,
    issueType_id int unsigned not null,
    reportedDate date not null,
    resolvedDate date,
    comments text,
    foreign key (meter_id)     references meters    (id),
    foreign key (issueType_id) references issueTypes(id)
);

insert into temp
        (meter_id,   issueType_id,   reportedDate,   resolvedDate,   comments)
select i.meter_id, t.issueType_id, i.reportedDate, i.resolvedDate, i.comments
from issue_issueTypes t
join issues i on t.issue_id=i.id;

drop table issue_issueTypes;
drop table issues;
rename table temp to issues;

alter table issues drop resolvedDate;

create table workTypes (
    id int unsigned not null primary key auto_increment,
    name varchar(32) not null,
    description varchar(255)
);
