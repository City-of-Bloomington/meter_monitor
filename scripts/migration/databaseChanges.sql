create table issueTypeGroups (
    id   int unsigned not null primary key auto_increment,
    name varchar(32)  not null
);
insert into issueTypeGroups set name='Other';

alter table issueTypes add issueTypeGroup_id int unsigned not null;
update issueTypes set issueTypeGroup_id=1;
alter table issueTypes add foreign key (issueTypeGroup_id) references issueTypeGroups(id);
